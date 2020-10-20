#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);

	ofEnableDepthTest();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 55, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	string word = "ROTATING";
	auto path_list = font.getStringAsPoints(word, true, false);
	for (auto& path : path_list) {

		vector<ofPolyline> outline = path.getOutline();

		for (int y = -240; y <= 240; y += 60) {

			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				if (outline_index != 0) { ofNextContour(true); }

				outline[outline_index] = outline[outline_index].getResampledByCount(150);
				auto vertices = outline[outline_index].getVertices();
				for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

					auto location = glm::vec3(vertices[vertices_index].x - this->font.stringWidth(word) * 0.5, y + vertices[vertices_index].y + this->font.stringHeight(word) * 0.5, 0);
					auto angle_y = ofMap(ofNoise((y + location.y) * 0.001 + ofGetFrameNum() * 0.01), 0, 1, -PI * 5, PI * 5);
					auto rotation_z = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
					location = glm::vec4(location, 0) * rotation_z;

					ofVertex(location);
				}
			}
			ofEndShape(true);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}