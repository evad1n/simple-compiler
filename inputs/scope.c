void main() {
    int x = 5;
    cout << x << endl;
    {
        int x = 10;
        cout << x << endl;
    }
    cout << x << endl;
}