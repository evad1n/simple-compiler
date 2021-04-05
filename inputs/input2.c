void main() {
   int x;
   x = 10;
   int y = x + 5;
   int z = x ? (y * 10 / 5) : 45;
   cout << x << endl;
   cout << y << endl;
   cout << z << endl;

   int a = 0;
   int b = 1;

   cout << (a & b) << endl;
   cout << (a & b && 1) << endl;
   cout << (1 + a & b && 0) << endl;
   cout << (1 + a & b && 1) << endl;
   // cin >> x;
   // if (x == 1)
   //    cout << x << endl;
   // else if (x == 2)
   //    cout << x << endl;
   // else if (x == 3)
   //    cout << x << endl;
   // else
   //    cout << x << endl;
}
