void main() {
    int x = 5;
    cout << x << endl;
    {
        cout << x << endl;
        int x = 10;
        cout << x << endl;
    }
    cout << x << endl;
    // int x = 5;
    // cout << -x << endl;
    // x = (x < 2) ? 0 : 10;
    // cout << x << endl;
    // x += 5;
    // cout << x << endl;
    // if (!(x < 8)) {
    //     cout << 20;
    // }

}