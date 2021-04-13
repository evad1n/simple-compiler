void main() {
    int x = 5;
    cout << x << endl;
    {
        cout << x << endl;
        int x = 10;
        cout << x << endl;
        x++;
        cout << x << endl;
        x /= 3;
        cout << x << endl;
    }
    cout << x << endl;
    x--;
    cout << x << endl;

    int y;
    cin >> y;
    cout << y << endl;

    int z = 5;

    cout << endl << x << endl;
    cout << y << endl;
    cout << z << endl;
}