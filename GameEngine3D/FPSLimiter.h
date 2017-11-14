#pragma once

namespace GameEngine3D {

	class FPSLimiter {
	public: 
		void initialise(float maxFPS);

		void setMaxFPS(float maxFPS);

		float begin();

		float end();

		float getFPS() { return _fps; }

	private:

		void calculateFPS();

		float _maxFPS;
		float _frameTime;
		float _fps;

		unsigned int _startTicks;
		unsigned int _endTicks;
	};

};