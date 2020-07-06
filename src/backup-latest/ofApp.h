#pragma once


#include "ofMain.h"
#include "ofxSpatialHash.h"
#include "ofxGui.h"
#include "ofxInputField.h"

class ofApp : public ofBaseApp
{
public:

	typedef glm::vec2 Vec2;
	typedef glm::vec3 Vec3;

	ofxIntSlider subdivision;
	ofxIntSlider numObj;
	ofxToggle kdtree;
	ofxLabel fps;
	ofxPanel gui;


	ofApp();
	void setup() override;
	void update() override;
	void draw() override;

	//void mousePressed(ofMouseEventArgs &mouse) override;

	enum
	{
		DEFAULT_RADIUS = 200,
		DEFAULT_NEAREST_N = 200
	};

	std::vector<Vec2> points, child1, child2, child11, child12, child21, child22, child111, child112, child121, child122, child211, child212, child221, child222;
	std::vector<Vec3> position;

	ofx::KDTree<Vec2> hash, firstchild, secondchild, grandchild1, grandchild2, grandchild3, grandchild4, 
		ggrandchild1, ggrandchild2, ggrandchild3, ggrandchild4, ggrandchild5, ggrandchild6, ggrandchild7, ggrandchild8;
	ofx::KDTree<Vec2>::SearchResults searchResults;

	ofMesh mesh;

	enum Modes
	{
		MODE_RADIUS,
		MODE_NEAREST_N
	};

	Vec2 sample, minP, minPt, minBrtt;
	Vec2 mid, midc1, midc2, midcc1, midcc2, midcc3, midcc4;
	int mode = 0;
	int num = 50;
	int temp = 50;
	std::stringstream strm;
	int radius = 0;
	int numObject = 50;
	int middlec1, middlec2, middlecc1, middlecc2, middlecc3, middlecc4;
	int nearestN = 0;
	float time;
	float minBrt = 1000;
	float minVal, minM = 10000;

	void numObjChanged(int numchange);
	void reset();
	void getMidNode();
	void sortX(std::vector<Vec2> &vec);
	void sortY(std::vector<Vec2>& vec);

	void calcDist(std::vector<Vec2>& vec);
	void searchReg(Vec2 temp);
	void brutesearch(Vec2 temp);

	int c1, c2 = 0;
};