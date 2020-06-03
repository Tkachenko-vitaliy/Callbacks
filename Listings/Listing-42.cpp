#include "Listing-41.h"

int main()
{
	int capture = 10;
	auto lambda = [capture](int eventID) {/*this is a body of lambda*/};
	Initiator<decltype(lambda)> callbackLambda1(lambda); // Ok, initialization in constructor
	Initiator<decltype(lambda)> callbackLambda = lambda; // Ok, implicit constructor call
	//Initiator<decltype(lambda)> callbackLambda2;  //Error: attempting to reference a deleted function
	//callbackLambda.setup(lambda);  //Error:  ‘operator’ =  attempting to reference a deleted function
	callbackLambda.run();

}