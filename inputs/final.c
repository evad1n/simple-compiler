void main() {
    int x = 20;
    int y = 30;
    int z = 40;

    if ((y < x) or (z > x))
        cout << 100 << endl;
    if ((y < x) || (z > x))
        cout << 100 << endl;

    if ((y < x) and (z > x))
        cout << 200 << endl;
    if ((y < x) && (z > x))
        cout << 200 << endl;

    z *= 20;
    cout << z << endl;


    int a = 5;
    int b = 25;
    do {
        cout << a << endl;
        a += 5;
    } while (a < b);

    a = 0;
    b = 1;
    do
        cout << 100 << endl;
    while (a == b);

    a = 0;
    b = 1;
    while (a == b)
        cout << 200 << endl;
}