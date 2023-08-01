#pragma once

class Easing final
{
private:
	Easing() = default;
	~Easing() = default;

public: //ÉÅÉìÉoä÷êî
	static inline float easeIn(float time, float maxTime, float maxPos, float nowPos) {
		maxPos -= nowPos;
		time /= maxTime;

		return maxPos * time * time + nowPos;
	}

	static inline float easeOut(float time, float maxTime, float maxPos, float nowPos) {
		maxPos -= nowPos;
		time /= maxTime;

		return -maxPos * time * (time - 2.0f) + nowPos;
	}

	static inline float easeInOut(float time, float maxTime, float maxPos, float nowPos) {
		maxPos -= nowPos;
		time /= maxTime;

		if (maxTime / 2.0f < time) return maxTime / 2.0f * time * time + nowPos;

		return -maxPos * time * (time - 2.0f) + nowPos;
	}

	static inline float easeInBack(float time, float maxTime, float maxPos, float nowPos, float back = 1.70158f) {
		maxPos -= nowPos;
		time /= maxTime;

		return maxPos * time * time * ((back + 1) * time - back) + nowPos;
	}

	static inline float easeOutBack(float time, float maxTime, float maxPos, float nowPos, float back = 1.70158f) {
		maxPos -= nowPos;
		time = time / maxTime - 1;

		return maxPos * (time * time * ((back + 1) * time * back) + 1) + nowPos;
	}

	static inline float easeOutBounce(float time, float maxTime, float nowPos, float maxPos) {
		const float n1 = 7.5625f;
		const float d1 = 2.75f;

		maxPos -= nowPos;
		time /= maxTime - 1.0f;

		if (time < 1.0f / d1) {
			float t = time;
			return maxPos * (n1 * t * t) + nowPos;
		}
		else if (time < 2.0f / d1) {
			float t = time - 1.5f / d1;
			return maxPos * (n1 * t * t + 0.75f) + nowPos;
		}
		else if (time < 2.5f / d1) {
			float t = time - 2.25f / d1;
			return maxPos * (n1 * t * t + 0.9375f) + nowPos;
		}
		else {
			float t = time - 2.625f / d1;
			return maxPos * (n1 * t * t + 0.984375f) + nowPos;
		}
	}
};

