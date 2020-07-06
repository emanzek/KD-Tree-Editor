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
	ofxIntSlider numnodes;
	ofxToggle kdtree;
	ofxLabel fps;
	ofxPanel gui;


	ofApp();
	void setup() override;
	void update() override;
	void draw() override;

	void keyPressed(int key) override;

	enum
	{
		DEFAULT_RADIUS = 200,
		DEFAULT_NEAREST_N = 200
	};

	std::vector<Vec2> points, child1, child2, child;
	std::vector<Vec3> position;

	ofx::KDTree<Vec2> hash, firstchild, secondchild, childd;
	ofx::KDTree<Vec2>::SearchResults searchResults;

	ofMesh mesh;

	enum Modes
	{
		MODE_RADIUS,
		MODE_NEAREST_N
	};

	int mode = 0;
	int num = 10;
	int temp = 10;
	std::stringstream strm;
	int radius = 0;
	int numNodes = 100;

	int nearestN = 0;

	void numNodesChanged(int numchange);
	void reset();
	void getMidNode();
	void sortX();
	void sortY();
	void sortYc1();
	void sortYc2();

	void anak(std::vector<Vec2> &vec);
	void sortByX(std::vector<Vec2> &vec);
	void sortByY(std::vector<Vec2> &vec);

	int c1, c2 = 0;
};