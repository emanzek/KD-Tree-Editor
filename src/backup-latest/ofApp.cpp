#include "ofApp.h"

ofApp::ofApp() :
	hash(points),
	firstchild(child1),
	secondchild(child2),
	grandchild1(child11), grandchild2(child12), grandchild3(child21), grandchild4(child22),
	ggrandchild1(child111), ggrandchild2(child112), ggrandchild3(child121), ggrandchild4(child122),
	ggrandchild5(child211), ggrandchild6(child212), ggrandchild7(child221), ggrandchild8(child222)
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
	gui.add(subdivision.setup("KD-Tree Depth", 3, 1, 10));


	if (num != temp) num = temp;
	gui.add(numObj.setup("numObject", num, 2, 200));
	numObjChanged(numObj);
	temp = numObj;
	gui.add(kdtree.setup("KDTREE Mode", true));
	gui.add(fps.setup("FPS:", strm.str()));

	getMidNode();
}

void ofApp::reset() {
	points.clear();
	mesh.clear();
	child1.clear();child11.clear();child111.clear();child112.clear();child12.clear();child121.clear();child122.clear();
	child2.clear();child21.clear();child211.clear();child212.clear();child22.clear();child221.clear();child222.clear();
	
}

void ofApp::numObjChanged(int numchange) {
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
	if (temp != numObj) {
		reset();
		numObjChanged(numObj);
		temp = numObj;
		getMidNode();
	}

	//if (child1.size() != c1 || child2.size() != c2) {
	//	child1.clear();
	//	child2.clear();
	//}

	std::stringstream strm1;
	strm1 << "fps: " << ofGetFrameRate();
	fps = strm1.str();

	if (ofGetMousePressed(0)) {
		minVal = minM;
		minPt = minP;
	}
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
	if (kdtree) {
		ofDrawLine(Vec2(mid.x, ofGetHeight()), Vec2(mid.x, 0));	//Draw X midline
		ofDrawLine(Vec2(0, midc1.y), Vec2(mid.x, midc1.y));  //Draw Y midline
		ofDrawLine(Vec2(midcc1.x, 0), Vec2(midcc1.x, midc1.y));  //Draw Y midline
		ofDrawLine(Vec2(midcc2.x, midc1.y), Vec2(midcc2.x, ofGetHeight()));  //Draw Y midline
		ofDrawLine(Vec2(mid.x, midc2.y), Vec2(ofGetWidth(), midc2.y));  //Draw Y midline
		ofDrawLine(Vec2(midcc3.x, 0), Vec2(midcc3.x, midc2.y));  //Draw Y midline
		ofDrawLine(Vec2(midcc4.x, midc2.y), Vec2(midcc4.x, ofGetHeight()));  //Draw Y midline


		if (ofGetMousePressed(0)) {
			time = ofGetElapsedTimef();
			sample = { ofGetMouseX(), ofGetMouseY() };
			std::cout << sample << endl;
			searchReg(sample);
			ofFill();
			ofSetColor(0, 255, 0);
			ofDrawCircle(minPt, 10);
			//std::cout << time << endl;
			ofResetElapsedTimeCounter();
		}
	}
	else {
		if (ofGetMousePressed(0)) {
			time = ofGetElapsedTimef();
			sample = { ofGetMouseX(), ofGetMouseY() };
			std::cout << sample << endl;
			brutesearch(sample);
			std::cout << ofGetElapsedTimef() << endl;
			ofResetElapsedTimeCounter();
			ofFill();
			ofSetColor(0, 255, 0);
			ofDrawCircle(minBrtt, 10);
			//std::cout << time << endl;
			ofResetElapsedTimeCounter();

		}
	}
	
	ofFill();
	ofSetColor(0, 255, 0);
	ofDrawCircle(sample, 10);
}


//void ofApp::mousePressed(ofMouseEventArgs &mouse)
//{
//}

void ofApp::getMidNode() {
	int index = 0;
	
	sortX(points);
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
	
	//ofDrawLine(Vec2(mid.x, ofGetHeight()), Vec2(mid.x, 0));	//Draw X midline
	
		child1.clear();child2.clear();
			for (int j = 0; j < points.size(); j++) {
				if (points.at(j).x < points.at(middle).x) {
					child1.push_back(points[j]);
				}
				if (points.at(j).x >= points.at(middle).x) {
					child2.push_back(points[j]);
				}
			}

	//std::cout << endl;
	//std::cout << "C1 SIZE" << endl;
	//std::cout << c1 << endl;
	//std::cout << endl;
	//std::cout << "C2 SIZE" << endl;
	//std::cout << c2 << endl;
	//std::cout << endl;
	//std::cout << "CHILD1 SIZE"<< endl;
	//std::cout << child1.size()<< endl;
	//std::cout << endl;
	//std::cout << "CHILD2 SIZE" << endl;
	//std::cout << child2.size() << endl;
	//

			if (child1.size() > 1) {
				sortY(child1);
				middlec1 = (child1.size() / 2);	//find middle array size
				for (int i = 0; i < child1.size(); i++) {
					for (int j = 0; j < child1.size() - 1; j++) {
						midc1 = child1.at(middlec1);	//set middle array = mid
					}
				}
				/*std::cout << endl;
				std::cout << "midc1" << endl;
				std::cout << midc1 << endl;*/
				
				//ofDrawLine(Vec2(0, midc1.y), Vec2(mid.x, midc1.y));  //Draw Y midline

				child11.clear();child12.clear();
				for (int j = 0; j < child1.size(); j++) {
					if (child1.at(j).y < child1.at(middlec1).y) {
						child11.push_back(child1[j]);
					}
					if (child1.at(j).y >= child1.at(middlec1).y) {
						child12.push_back(child1[j]);
					}
				}

				if (child11.size() > 1) {
					sortX(child11);
					int middlecc1 = (child11.size() / 2);	//find middle array size
					for (int i = 0; i < child11.size(); i++) {
						for (int j = 0; j < child11.size() - 1; j++) {
							midcc1 = child11.at(middlecc1);	//set middle array = mid
						}
					}
					/*std::cout << endl;
					std::cout << "midc2" << endl;
					std::cout << midcc1 << endl;*/
					
					//ofDrawLine(Vec2(midcc1.x, 0), Vec2(midcc1.x, midc1.y));  //Draw Y midline

					child111.clear();child112.clear();
					for (int j = 0; j < child11.size(); j++) {
						if (child11.at(j).x < child11.at(middlecc1).x) {
							child111.push_back(child11[j]);
						}
						if (child11.at(j).x >= child11.at(middlecc1).x) {
							child112.push_back(child11[j]);
						}
					}
				}

				if (child12.size() > 1) {
					sortX(child12);
					int middlecc2 = (child12.size() / 2);	//find middle array size
					for (int i = 0; i < child12.size(); i++) {
						for (int j = 0; j < child12.size() - 1; j++) {
							midcc2 = child12.at(middlecc2);	//set middle array = mid
						}
					}
					/*std::cout << endl;
					std::cout << "midc2" << endl;
					std::cout << midcc2 << endl;*/
					
					//ofDrawLine(Vec2(midcc2.x, midc1.y), Vec2(midcc2.x, ofGetHeight()));  //Draw Y midline
					
					child121.clear();child122.clear();
					for (int j = 0; j < child12.size(); j++) {
						if (child12.at(j).x < child12.at(middlecc2).x) {
							child121.push_back(child12[j]);
						}
						if (child12.at(j).x >= child12.at(middlecc2).x) {
							child122.push_back(child12[j]);
						}
					}
				}
			}

			if (child2.size() > 1) {
				sortY(child2);
				middlec2 = (child2.size() / 2);	//find middle array size
				for (int i = 0; i < child2.size(); i++) {
					for (int j = 0; j < child2.size() - 1; j++) {
						midc2 = child2.at(middlec2);	//set middle array = mid
					}
				}
				/*std::cout << endl;
				std::cout << "midc2" << endl;
				std::cout << midc2 << endl;*/
				
				//ofDrawLine(Vec2(mid.x, midc2.y), Vec2(ofGetWidth(), midc2.y));  //Draw Y midline

				child21.clear();child22.clear();
				for (int j = 0; j < child2.size(); j++) {
					if (child2.at(j).y < child2.at(middlec2).y) {
						child21.push_back(child2[j]);
					}
					if (child2.at(j).y >= child2.at(middlec2).y) {
						child22.push_back(child2[j]);
					}
				}
				if (child21.size() > 1) {
					sortX(child21);
					int middlecc3 = (child21.size() / 2);	//find middle array size
					for (int i = 0; i < child21.size(); i++) {
						for (int j = 0; j < child21.size() - 1; j++) {
							midcc3 = child21.at(middlecc3);	//set middle array = mid
						}
					}
					/*std::cout << endl;
					std::cout << "midc2" << endl;
					std::cout << midcc3 << endl;*/
					
					//ofDrawLine(Vec2(midcc3.x, 0), Vec2(midcc3.x, midc2.y));  //Draw Y midline
					
					child211.clear();child212.clear();
					for (int j = 0; j < child21.size(); j++) {
						if (child21.at(j).x < child21.at(middlecc3).x) {
							child211.push_back(child21[j]);
						}
						if (child21.at(j).x >= child21.at(middlecc3).x) {
							child212.push_back(child21[j]);
						}
					}
				}

				if (child22.size() > 1) {
					sortX(child22);
					int middlecc4 = (child22.size() / 2);	//find middle array size
					for (int i = 0; i < child22.size(); i++) {
						for (int j = 0; j < child22.size() - 1; j++) {
							midcc4 = child22.at(middlecc4);	//set middle array = mid
						}
					}
					/*std::cout << endl;
					std::cout << "midc4" << endl;
					std::cout << midcc4 << endl;*/
					
					//ofDrawLine(Vec2(midcc4.x, midc2.y), Vec2(midcc4.x, ofGetHeight()));  //Draw Y midline
					
					child221.clear();child222.clear();
					for (int j = 0; j < child22.size(); j++) {
						if (child22.at(j).x < child22.at(middlecc4).x) {
							child221.push_back(child22[j]);
						}
						if (child22.at(j).x >= child22.at(middlecc4).x) {
							child222.push_back(child22[j]);
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

void ofApp::calcDist(std::vector<Vec2>& vec) {
	float min = 10000;
	for (int i = 0; i < vec.size(); i++) {
		float dist = ofDistSquared(sample.x, sample.y, vec[i].x, vec[i].y);
		if ((dist < min) && (dist < minM)) {
			min = dist;
			minM = dist;
			minP = vec[i];
		}
	}
}

void ofApp::searchReg(Vec2 samples) {
	float minimum = 10000;
	vector<Vec2> middle = { mid, midc1, midc2, midcc1, midcc2, midcc3, midcc4 };
	for (int i = 0; i < middle.size(); i++) {
		float distance = ofDistSquared(samples.x, samples.y, middle[i].x, middle[i].y);
		if (distance < minM) {
			minM = distance;
			minP = middle[i];
		}
	}

	if ((samples.x < mid.x) && (child1.size() > 0)) {
		if ((samples.y < midc1.y) && (child11.size() > 0)) {
			if ((samples.x < midcc1.x) && (child111.size() > 0)) calcDist(child111);
			else if((samples.x >= midcc1.x) && (child112.size() > 0)) calcDist(child112);
		}
		else if ((samples.y >= midc1.y) && (child12.size() > 0)) {
			if ((samples.x < midcc2.x) && (child121.size() > 0)) calcDist(child121);
			else if ((samples.x >= midcc2.x) && (child122.size() > 0)) calcDist(child122);
		}
	}
	else if ((samples.x >= mid.x) && (child2.size() > 0)) {
		if ((samples.y < midc2.y) && (child21.size() > 0)) {
			if ((samples.x < midcc3.x) && (child211.size() > 0)) calcDist(child211);
			else if ((samples.x >= midcc3.x) && (child212.size() > 0)) calcDist(child212);
		}
		else if ((samples.y >= midc2.y) && (child22.size() > 0)) {
			if ((samples.x < midcc4.x) && (child221.size() > 0)) calcDist(child221);
			else if ((samples.x >= midcc4.x) && (child222.size() > 0))  calcDist(child222);
		}
	}

}

void ofApp::brutesearch(Vec2 samples) {
	for (int i = 0; i < points.size(); i++) {
		float distance = ofDistSquared(samples.x, samples.y, points[i].x, points[i].y);
		if (distance < minBrt)
			minBrt = distance;
			minBrtt = points[i];
		}
	}
