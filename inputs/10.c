void main() {
	int sum;
	sum = 35 + 400;
	cout << sum << endl;
	if (sum > 400)
		cout << 123 << endl;
	sum += 10;
	cout << sum << endl;
	if (sum > 10000)
		cout << 10000 << endl;
	cout << endl;

	while (sum < 10000) {
		cout << sum << endl;
		sum *= 2;
	}
	cout << endl << sum << endl;

}