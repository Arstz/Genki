#include "AnimationTask.h"
#include "Animation.h"
#define M_PI 3.14159265358979323846f  /* pipiska */

float AnimationTask::calculatePosition(float startPosition, float endPosition, const float& startTime, const float& endTime, const float& currentTime)
{
	return startPosition + (endPosition - startPosition) * ((currentTime - startTime) / (endTime - startTime));
}

float AnimationTask::calculatePosition(float startPosition, float endPosition, const float& startTime, const float& endTime, const float& currentTime, const float& limit)
{
	if (float(endPosition - startPosition) < float(-limit / 2)) {	
		startPosition -= limit;
	}
	else if (float(endPosition - startPosition) > float(limit / 2)) {
		endPosition -= limit;
	}
	return startPosition + (endPosition - startPosition) * ((currentTime - startTime) / (endTime - startTime));
}

void AnimationTask::animate(float& frameTime)
{
	timer += frameTime;
	while (timer > (*animation).timeKeys[counter])
	{
		counter += 1;
		if (counter == (*animation).keyCount)
		{
			timer -= (*animation).timeKeys[counter - 1];
			counter = 0;
		}
	}
	if (counter) {
		*target = calculatePosition(
			(*animation).stateKeys[counter - 1],
			(*animation).stateKeys[counter],
			(*animation).timeKeys[counter - 1],
			(*animation).timeKeys[counter],
			timer
		);
	}
	else {
		*target = calculatePosition(
			(*animation).stateKeys[(counter + (*animation).keyCount - 1) % (*animation).keyCount],
			(*animation).stateKeys[counter],
			0.f,
			(*animation).timeKeys[counter],
			timer
		);
	}
}