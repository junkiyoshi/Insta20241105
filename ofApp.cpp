#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	float span = 15;
	ofColor color;
	float len = 300;

	float angle;
	glm::highp_mat4 rotation;
	for (float i = 0; i <= 6; i++) {

		for (float x = len * -0.5; x < len * 0.5; x += span) {

			for (float y = len * -0.5; y < len * 0.5; y += span) {

				if (i <= 4) {

					angle = PI * 0.5 * i;
					rotation = glm::rotate(glm::mat4(), angle, glm::vec3(0, 1, 0));
				}

				if (i == 5) {

					angle = PI * 0.5;
					rotation = glm::rotate(glm::mat4(), angle, glm::vec3(1, 0, 0));
				}

				if (i == 6) {

					angle = PI * 0.5 * 3;
					rotation = glm::rotate(glm::mat4(), angle, glm::vec3(1, 0, 0));
				}

				glm::vec3 noise_location = glm::vec4(x, y, len * 0.5, 0) * rotation;
				int noise_value = ofMap(ofNoise(noise_location.x * 0.01, noise_location.y * 0.01, noise_location.z * 0.01 + ofGetFrameNum() * 0.001), 0, 1, 0, 20);

				if (noise_value % 2 == 0) {

					continue;
				}

				ofColor color(239);

				vector<glm::vec3> vertices;
				vertices.push_back(glm::vec4(x, y, len * 0.5, 0) * rotation);
				vertices.push_back(glm::vec4(x + span, y, len * 0.5, 0) * rotation);
				vertices.push_back(glm::vec4(x + span, y + span, len * 0.5, 0) * rotation);
				vertices.push_back(glm::vec4(x, y + span, len * 0.5, 0) * rotation);
				this->mesh.addVertices(vertices);

				this->mesh.addColor(color); this->mesh.addColor(color);
				this->mesh.addColor(color); this->mesh.addColor(color);

				this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 4); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
				this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.72);
	ofRotateX(ofGetFrameNum() * 1.44);

	this->mesh.draw();

	ofFill();
	ofSetColor(0);
	ofDrawBox(299);

	this->cam.end();

	/*
	int start = 40;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}