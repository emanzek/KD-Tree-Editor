#include "ofApp.h"

ofApp::ofApp() :
	hash(points),
	firstchild(child1), secondchild(child2),
	grandchild1(cchild1), grandchild2(cchild2), grandchild3(cchild3), grandchild4(cchild4),
	ggc1(ccc1), ggc2(ccc2), ggc3(ccc3), ggc4(ccc4), ggc5(ccc5), ggc6(ccc6), ggc7(ccc7), ggc8(ccc8),
	gggc1(cccc1), gggc2(cccc2), gggc3(cccc3), gggc4(cccc4), gggc5(cccc5), gggc6(cccc6), gggc7(cccc7), gggc8(cccc8), 
	gggc9(cccc9), gggc10(cccc10), gggc11(cccc11), gggc12(cccc12), gggc13(cccc13), gggc14(cccc14), gggc15(cccc15), gggc16(cccc16)
{
}

void ofApp::setup()
{
	ofEnableAlphaBlending();
	mesh.setMode(OF_PRIMITIVE_POINTS);
	gui.setup();
	gui.add(subdivision.setup("KD-Tree Depth", 4, 1, 10));


	if (num != temp) num = temp;
	gui.add(numObj.setup("numObject", num, 0, 100));
	numObjChanged(numObj);
	temp = numObj;
	gui.add(kdtree.setup("KDTREE Mode", true));
	gui.add(fps.setup("FPS:", strm.str()));
}

void ofApp::reset() {
	points.clear();
	mesh.clear();
	child1.clear();
	child2.clear();
}


void ofApp::numObjChanged(int numchange) {
	for (std::size_t i = 0; i < numchange; ++i)
	{
		Vec2 point(ofRandom(100, ofGetWidth() - 100),
			ofRandom(100, ofGetHeight() - 100));

		points.push_back(point);
	}
}

void ofApp::update()
{
	if (temp != numObj) {
		reset();
		numObjChanged(numObj);
		temp = numObj;
	}

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

	mesh.draw(); //Draw all of the points.

	gui.draw();

	ofNoFill();
	ofSetColor(255, 0, 0);
	if (kdtree)	KDTreePartition();

}

void ofApp::KDTreePartition() {
	int index = 0;

	if (points.size() > 0) {

		Vec2 mid;
		int middle;
		int left = ofGetHeight();
		int right = 0;
		PartitionX(points, mid, middle, child1, child2, left, right);

		if (child1.size() > 0) {

			Vec2 midc1;
			int middlec1;
			int left = 0;
			int right = mid.x;
			PartitionY(child1, midc1, middlec1, cchild1, cchild2, left, right);

			
			if (cchild1.size() > 0) {

				Vec2 midcc1;
				int middlecc1;
				int left = 0;
				int right = midc1.y;
				PartitionX(cchild1, midcc1, middlecc1, ccc1, ccc2, left, right);

				if (ccc1.size() > 0) {

					Vec2 midccc1;
					int middleccc1;
					int left = 0;
					int right = midcc1.x;
					PartitionY(ccc1, midccc1, middleccc1, cccc1, cccc2, left, right);
				}

				if (ccc2.size() > 0) {

					Vec2 midccc2;
					int middleccc2;
					int left = midcc1.x;
					int right = mid.x;
					PartitionY(ccc2, midccc2, middleccc2, cccc3, cccc4, left, right);
				}
				
			}

			if (cchild2.size() > 0) {

				Vec2 midcc2;
				int middlecc2;
				int left = midc1.y;
				int right = ofGetHeight();
				PartitionX(cchild2, midcc2, middlecc2, ccc3, ccc4, left, right);

				if (ccc3.size() > 0) {

					Vec2 midccc3;
					int middleccc3;
					int left = 0;
					int right = midcc2.x;
					PartitionY(ccc3, midccc3, middleccc3, cccc5, cccc6, left, right);
				}

				if (ccc4.size() > 0) {

					Vec2 midccc4;
					int middleccc4;
					int left = midcc2.x;
					int right = mid.x;
					PartitionY(ccc4, midccc4, middleccc4, cccc7, cccc8, left, right);
				}

			}

		}

		if (child2.size() > 0) {

			Vec2 midc2;
			int middlec2;
			int left = mid.x;
			int right = ofGetWidth();
			PartitionY(child2, midc2, middlec2, cchild3, cchild4, left, right);
			
			if (cchild3.size() > 0) {

				Vec2 midcc3;
				int middlecc3;
				int left = 0;
				int right = midc2.y;
				PartitionX(cchild3, midcc3, middlecc3, ccc5, ccc6, left, right);

				if (ccc5.size() > 0) {

					Vec2 midccc5;
					int middleccc5;
					int left = mid.x;
					int right = midcc3.x;
					PartitionY(ccc5, midccc5, middleccc5, cccc9, cccc10, left, right);
				}

				if (ccc6.size() > 0) {

					Vec2 midccc6;
					int middleccc6;
					int left = midcc3.x;
					int right = ofGetWidth();
					PartitionY(ccc6, midccc6, middleccc6, cccc11, cccc12, left, right);
				}
				
			}

			if (cchild4.size() > 0) {

				Vec2 midcc4;
				int middlecc4;
				int left = midc2.y;
				int right = ofGetHeight();
				PartitionX(cchild4, midcc4, middlecc4, ccc7, ccc8, left, right);

				if (ccc7.size() > 0) {

					Vec2 midccc7;
					int middleccc7;
					int left = mid.x;
					int right = midcc4.x;
					PartitionY(ccc7, midccc7, middleccc7, cccc13, cccc14, left, right);
				}

				if (ccc8.size() > 0) {

					Vec2 midccc8;
					int middleccc8;
					int left = midcc4.x;
					int right = ofGetWidth();
					PartitionY(ccc8, midccc8, middleccc8, cccc15, cccc16, left, right);
				}

			}
		}
	}
}

void ofApp::sortX(std::vector<Vec2> &vec) {

	/*std::cout << "before X sorting" << endl;
	for (auto x : vec) {
		std::cout << x.x << endl;
	}*/

	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec.size() - 1; j++) {
			if (vec.at(j).x > vec.at(j + 1).x) {
				std::iter_swap(vec.begin() + (j), vec.begin() + (j + 1));
			}
		}
	}

	/*std::cout << "after X sorting" << endl;
	for (auto x : vec) {
		std::cout << x.x << endl;
	}*/

}

void ofApp::sortY(std::vector<Vec2>& vec) {

	/*std::cout << "before Y sorting" << endl;
	for (auto x : vec) {
		std::cout << x.y << endl;
	}*/

	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec.size() - 1; j++) {
			if (vec.at(j).y > vec.at(j + 1).y) {
				std::iter_swap(vec.begin() + (j), vec.begin() + (j + 1));
			}
		}
	}

	/*std::cout << "after Y sorting" << endl;
	for (auto x : vec) {
		std::cout << x.y << endl;
	}*/

}


void ofApp::PartitionX(std::vector<Vec2> &vec, Vec2 &center, int &c, std::vector<Vec2> &vec1, std::vector<Vec2> &vec2, int &left, int &right) {
	
	std::cout << "Divide Space by X" << endl;
	sortX(vec);
	center;
	c = (vec.size() / 2) - 1;	//find middle array size

	if (vec.size() > 1) {
		for (int i = 0; i < vec.size(); i++) {
			for (int j = 0; j < vec.size() - 1; j++) {
				center = vec.at(c);	//set middle array = mid
			}
		}
	}
	else if (vec.size() == 1) {
		c = 0;
		center = vec.at(c);
	}

	//ofDrawLine(Vec2(min.x, mid.y), Vec2(max.x, mid.y));  //Draw Y midline
	ofDrawLine(Vec2(center.x, left), Vec2(center.x, right));	//Draw X midline

	vec1.clear(); vec2.clear();
	for (int j = 0; j < vec.size(); j++) {
		if (vec.at(j).x < vec.at(c).x) {
			vec1.push_back(vec[j]);
		}
		if (vec.at(j).x > vec.at(c).x) {
			vec2.push_back(vec[j]);
		}
	}
}

void ofApp::PartitionY(std::vector<Vec2> &vec, Vec2 &center, int &c, std::vector<Vec2> &vec1, std::vector<Vec2> &vec2, int &left, int &right) {
	
	std::cout << "Divide Space by Y" << endl;
	sortY(vec);
	center;
	c = (vec.size() / 2) - 1;	//find middle array size

	if (vec.size() > 1) {
		for (int i = 0; i < vec.size(); i++) {
			for (int j = 0; j < vec.size() - 1; j++) {
				center = vec.at(c);	//set middle array = mid
			}
		}
	}
	else if (vec.size() == 1) {
		c = 0;
		center = vec.at(c);
	}

	ofDrawLine(Vec2(left, center.y), Vec2(right, center.y));	//Draw Y midline

	vec1.clear(); vec2.clear();
	for (int j = 0; j < vec.size(); j++) {
		if (vec.at(j).y < vec.at(c).y) {
			vec1.push_back(vec[j]);
		}
		if (vec.at(j).y > vec.at(c).y) {
			vec2.push_back(vec[j]);
		}
	}
}
