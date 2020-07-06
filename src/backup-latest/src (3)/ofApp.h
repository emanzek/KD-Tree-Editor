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
	ofMesh mesh;

	ofApp();
	void setup() override;
	void update() override;
	void draw() override;
	void numObjChanged(int numchange);
	void reset();
	void KDTreePartition();
	void sortX(std::vector<Vec2> &vec);
	void sortY(std::vector<Vec2>& vec);
	void PartitionX(std::vector<Vec2> &vec, Vec2 &center, int &c, std::vector<Vec2> &vec1, std::vector<Vec2> &vec2, int &left, int &right);
	void PartitionY(std::vector<Vec2> &vec, Vec2 &center, int &c, std::vector<Vec2> &vec1, std::vector<Vec2> &vec2, int &left, int &right);
	//void mousePressed(ofMouseEventArgs &mouse) override;


	std::vector<Vec2> points, child1, child2, cchild1, cchild2, cchild3, cchild4;
	std::vector<Vec2> ccc1, ccc2, ccc3, ccc4, ccc5, ccc6, ccc7, ccc8;
	std::vector<Vec2> cccc1, cccc2, cccc3, cccc4, cccc5, cccc6, cccc7, cccc8, cccc9, cccc10, cccc11, cccc12, cccc13, cccc14, cccc15, cccc16;

	ofx::KDTree<Vec2> hash, firstchild, secondchild, grandchild1, grandchild2, grandchild3, grandchild4;
	ofx::KDTree<Vec2> ggc1, ggc2, ggc3, ggc4, ggc5, ggc6, ggc7, ggc8;
	ofx::KDTree<Vec2> gggc1, gggc2, gggc3, gggc4, gggc5, gggc6, gggc7, gggc8, gggc9, gggc10, gggc11, gggc12, gggc13, gggc14, gggc15, gggc16;

	std::stringstream strm;

	int num = 10;
	int temp = 10;
	int numObject = 100;
	int middlec1, middlec2, middlecc1, middlecc2, middlecc3, middlecc4;

};