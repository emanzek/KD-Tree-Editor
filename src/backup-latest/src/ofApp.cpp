#include "ofApp.h"

ofApp::ofApp() :
	hash(points),
	firstchild(child1),
	secondchild(child2),
	childd(child)
	//mode(MODE_RADIUS),
	//radius(DEFAULT_RADIUS),
	//nearestN(DEFAULT_NEAREST_N)
{
}

void ofApp::setup()
{
	ofEnableAlphaBlending();
	mesh.setMode(OF_PRIMITIVE_POINTS);
	gui.setup();
	gui.add(subdivision.setup("subLevel", 0, 1, 10));

	if (num != temp) num = temp;
	gui.add(numnodes.setup("numNodes", num, 2, 100));
	numNodesChanged(numnodes);
	temp = numnodes;
	gui.add(kdtree.setup("KDTREE Mode", true));
	gui.add(fps.setup("FPS:", strm.str()));


}

void ofApp::reset() {
	points.clear();
	mesh.clear();
	child1.clear();
	child2.clear();
}

void ofApp::numNodesChanged(int numchange) {
	for (std::size_t i = 0; i < numchange; ++i)
	{
		Vec2 point(ofRandom(100, ofGetWidth() - 100),
			ofRandom(100, ofGetHeight() - 100));

		/*Vec2 point(ofRandom(0, ofGetWidth()),
			ofRandom(0, ofGetHeight()));*/

		points.push_back(point);
		//mesh.addVertex(Vec3(point.x, point.y, 0));
	}

	//hash.buildIndex();
}


void ofApp::update()
{
	searchResults.clear();
	if (temp != numnodes) {
		reset();
		numNodesChanged(numnodes);
		temp = numnodes;
	}

	//if (child1.size() != c1 || child2.size() != c2) {
	//	child1.clear();
	//	child2.clear();
	//}

	std::stringstream strm1;
	strm1 << "fps: " << ofGetFrameRate();
	fps = strm1.str();

}


void ofApp::draw()
{
	ofBackground(0);

	ofFill();
	ofSetColor(255);
	for (int i = 0; i < points.size(); i++) {

		ofDrawCircle(points[i], 10);
	}
	// Draw all of the points.
	//ofSetWidth(10);f
	mesh.draw();

	gui.draw();

	ofNoFill();
	ofSetColor(255, 0, 0);
	getMidNode();
}


void ofApp::keyPressed(int key)
{
}

void ofApp::getMidNode() {
	Vec2 max = Vec2(0, 0);
	Vec2 min = points[0];
	int index = 0;
	for (int i = 0; i < points.size(); i++) {
		if (max.x < points[i].x) max.x = points[i].x;
		if (max.y < points[i].y) max.y = points[i].y;
		if (min.x > points[i].x) min.x = points[i].x;
		if (min.y > points[i].y) min.y = points[i].y;
	}

	Vec2 minn = min;
	Vec2 maxx = max;

	ofDrawLine(Vec2(min.x, max.y), max);
	ofDrawLine(Vec2(max.x, min.y), max);
	ofDrawLine(min, Vec2(min.x, max.y));
	ofDrawLine(min, Vec2(max.x, min.y));


	sortByX(points);
	Vec2 mid;
	int middle = (points.size() / 2) - 1;	//find middle array size
	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < points.size() - 1; j++) {
			mid = points.at(middle);	//set middle array = mid
		}
	}

	//std::cout << endl;
	//std::cout << "MIDDLE" << endl;
	//std::cout<< mid<< endl;
	//ofDrawLine(Vec2(min.x, mid.y), Vec2(max.x, mid.y));  //Draw Y midline
	ofDrawLine(Vec2(mid.x, max.y), Vec2(mid.x, min.y));	//Draw X midline

	child1.clear();
	child2.clear();

	for (int j = 0; j < points.size(); j++) {
		if (points.at(j).x < points.at(middle).x) {
			child1.push_back(points[j]);
		}
		if (points.at(j).x > points.at(middle).x) {
			child2.push_back(points[j]);
		}
	}

	/*for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < points.size() - 1; j++) {
			if (points.at(j).x <= points.at(middle).x) {
				child1.push_back(points[j]);
			}
			if (points.at(j).x > points.at(middle).x) {
				child2.push_back(points[j]);
			}
		}
	}*/
	c1 = points.size() / 2;
	c2 = points.size() - c1;

	std::cout << endl;
	std::cout << "C1 SIZE" << endl;
	std::cout << c1 << endl;
	std::cout << endl;
	std::cout << "C2 SIZE" << endl;
	std::cout << c2 << endl;

	std::cout << endl;
	std::cout << "CHILD1 SIZE" << endl;
	std::cout << child1.size() << endl;

	std::cout << endl;
	std::cout << "CHILD2 SIZE" << endl;
	std::cout << child2.size() << endl;

	
	if (child1.size() > 1) {
		anak(child1);
		sortByY(child1);
		Vec2 midc1;
		int middlec1 = (child1.size() / 2);	//find middle array size
		for (int i = 0; i < c1; i++) {
			for (int j = 0; j < c1 - 1; j++) {
				midc1 = child1.at(middlec1);	//set middle array = mid
			}
		}
		std::cout << endl;
		std::cout << "midc1" << endl;
		std::cout << midc1 << endl;
		ofDrawLine(Vec2(minn.x, midc1.y), Vec2(mid.x, midc1.y));  //Draw Y midline
	}
	
	if (child2.size() > 1) {
		anak(child2);
		sortByY(child2);
		Vec2 midc2;
		int middlec2 = (child2.size() / 2);	//find middle array size
		for (int i = 0; i < c2; i++) {
			for (int j = 0; j < c2 - 1; j++) {
				midc2 = child2.at(middlec2);	//set middle array = mid
			}
		}
		std::cout << endl;
		std::cout << "midc2" << endl;
		std::cout << midc2 << endl;
		ofDrawLine(Vec2(mid.x, midc2.y), Vec2(maxx.x, midc2.y));  //Draw Y midline

	}
	
}


/*
void ofApp::createChild1(float width, float height, Vec2 midpoint, int level) {

	bool check = false;


	if (level < subdivision) {
		width /= 2;
		height /= 2;

		Vec2 upleft = Vec2(midpoint.x - width, midpoint.y - height);
		Vec2 bottomright = Vec2(midpoint.x + width, midpoint.y + height);


		for (int i = 0; i < points.size(); i++) {

			if (FindPoint(upleft.x, upleft.y, bottomright.x, bottomright.y, points[i].x, points[i].y)) {
				check = true;
				break;
			}
		}

		if (check) {
			ofDrawLine(Vec2(midpoint), Vec2(midpoint.x + width, midpoint.y));   //kanan
			ofDrawLine(Vec2(midpoint), Vec2(midpoint.x - width, midpoint.y));   //kiri
			ofDrawLine(Vec2(midpoint), Vec2(midpoint.x, midpoint.y + height));  //bawah
			ofDrawLine(Vec2(midpoint), Vec2(midpoint.x, midpoint.y - height));    //atas

			Vec2 newMid1 = Vec2(midpoint.x - width / 2, midpoint.y + height / 2);
			Vec2 newMid2 = Vec2(midpoint.x + width / 2, midpoint.y + height / 2);
			Vec2 newMid3 = Vec2(midpoint.x - width / 2, midpoint.y - height / 2);
			Vec2 newMid4 = Vec2(midpoint.x + width / 2, midpoint.y - height / 2);
			level++;

			createChild1(width, height, newMid1, level);  // bottom left
			createChild1(width, height, newMid2, level);    //bottom right
			createChild1(width, height, newMid3, level);    //up left
			createChild1(width, height, newMid4, level);  //up right

		}


	}
}

bool ofApp::FindPoint(int x1, int y1, int x2, int y2, int x, int y)
{
	if (x > x1 and x < x2 and y > y1 and y < y2)
		return true;

	return false;
}

void ofApp::createChild1off(float width, float height, Vec2 midpoint, int level) {

	if (level < subdivision) {
		width /= 2;
		height /= 2;

		Vec2 upleft = Vec2(midpoint.x - width, midpoint.y - height);
		Vec2 bottomright = Vec2(midpoint.x + width, midpoint.y + height);

		ofDrawLine(Vec2(midpoint), Vec2(midpoint.x + width, midpoint.y));   //kanan
		ofDrawLine(Vec2(midpoint), Vec2(midpoint.x - width, midpoint.y));   //kiri
		ofDrawLine(Vec2(midpoint), Vec2(midpoint.x, midpoint.y + height));  //bawah
		ofDrawLine(Vec2(midpoint), Vec2(midpoint.x, midpoint.y - height));    //atas

		Vec2 newMid1 = Vec2(midpoint.x - width / 2, midpoint.y + height / 2);
		Vec2 newMid2 = Vec2(midpoint.x + width / 2, midpoint.y + height / 2);
		Vec2 newMid3 = Vec2(midpoint.x - width / 2, midpoint.y - height / 2);
		Vec2 newMid4 = Vec2(midpoint.x + width / 2, midpoint.y - height / 2);
		level++;

		createChild1off(width, height, newMid1, level);  // bottom left
		createChild1off(width, height, newMid2, level);    //bottom right
		createChild1off(width, height, newMid3, level);    //up left
		createChild1off(width, height, newMid4, level);  //up right

	}
}
*/



void ofApp::anak(std::vector<Vec2> &vec) {
	Vec2 max = Vec2(0, 0);
	Vec2 min = vec[0];

	for (int i = 0; i < vec.size(); i++) {
		if (max.x < vec[i].x) max.x = vec[i].x;
		if (max.y < vec[i].y) max.y = vec[i].y;
		if (min.x > vec[i].x) min.x = vec[i].x;
		if (min.y > vec[i].y) min.y = vec[i].y;
	}
}

void ofApp::sortByX(std::vector<Vec2> &vec) {

	std::cout << "before X sorting" << endl;
	for (auto x : vec) {
		std::cout << x.x << endl;
	}

	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec.size() - 1; j++) {
			if (vec.at(j).x > vec.at(j + 1).x) {
				std::iter_swap(vec.begin() + (j), vec.begin() + (j + 1));
			}
		}
	}

	std::cout << "after X sorting" << endl;
	for (auto x : vec) {
		std::cout << x.x << endl;
	}

}

void ofApp::sortByY(std::vector<Vec2> &vec) {

	std::cout << "before Y sorting" << endl;
	for (auto x : vec) {
		std::cout << x.y << endl;
	}

	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec.size() - 1; j++) {
			if (vec.at(j).y > vec.at(j + 1).y) {
				std::iter_swap(vec.begin() + (j), vec.begin() + (j + 1));
			}
		}
	}

	std::cout << "after Y sorting" << endl;
	for (auto x : vec) {
		std::cout << x.y << endl;
	}

}