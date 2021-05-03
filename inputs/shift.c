void main() {
    int x = 24;
    int y = 2;
    cout << (x >> y) << endl; // 6
    cout << (x >> y - 1) << endl; // 12, not 5. -1 happens first
    cout << (x >> y == 2) << endl; // 0, not 12. ==2 happens after
}