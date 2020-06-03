int main()
{
	int capture = 10;

	auto lambda = [capture](int eventID) {/*this is a body of lambda*/};

	lambda(10); //lambda call
}
