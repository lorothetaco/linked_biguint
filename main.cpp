#include <iostream>
#include "BIGUINT.h"

using namespace std;


int main()
{
    BIGUINT b;
    cout << "Please type 12345: ";
    cin >> b;
    BIGUINT c("84497684976948574389573237634975648697498");
    BIGUINT d;
    BIGUINT e("0001");
    BIGUINT f = c;



    cout << b << ": size = " << b.size() <<  endl;
    cout << c << ": size = " << c.size() <<  endl;
    cout << d << ": size = " << d.size() <<  endl;
    cout << e << ": size = " << e.size() <<  endl;
    cout << f << ": size = " << f.size() <<  endl;

    f.ls(3);
    cout << f << ": size = " << f.size() <<  endl;
    f.rs(5);
    cout << f << ": size = " << f.size() <<  endl;
    f.rs(50);
    cout << f << ": size = " << f.size() <<  endl;


    BIGUINT b1(12346);
    cout << b1 << " vs. " << b << ": " << b1.compare(b) << endl;
    cout << b1 << " vs. " << b1 << ": " << b1.compare(b1) << endl;
    cout << b << " vs. " << b1 << ": " << b.compare(b1) << endl;
    cout << e << " vs. " << f << ": " << e.compare(f) << endl;
    cout << e << " vs. " << b << ": " << e.compare(b) << endl;

    cout << b << " + " << c << " = " << b + c << endl;
    cout << c << " + " << b << " = " << c + b << endl;
    cout << c << " + " << BIGUINT() << " = " << c + BIGUINT() << endl;
    cout << BIGUINT() << " + " << c << " = " << BIGUINT() + c << endl;

    cout << BIGUINT(123) << " - " << BIGUINT(29) << " = " << BIGUINT(123) - BIGUINT(29) << endl;
    cout << BIGUINT(123) << " - " << BIGUINT(123) << " = "  << BIGUINT(123) - BIGUINT(123) << endl;
    cout << BIGUINT(29) << " - " << BIGUINT(123) << " = " << BIGUINT(29) - BIGUINT(123) << endl;
    cout << c - b << endl;

    for (int i = 0; i < 10; ++i)
    {
        BIGUINT temp(b);
        cout << temp;
        temp *= i;
        cout << " * " << i << " = " << temp << endl;
    }

    cout << BIGUINT(12) << " * "  << BIGUINT(34) << " = " << BIGUINT(12) * BIGUINT(34) << endl;
    cout << BIGUINT(12) << " * "  << BIGUINT(3456) << " = " << BIGUINT(12) * BIGUINT(3456) << endl;
    cout << BIGUINT(1234) << " * " << BIGUINT(56) << " = " << BIGUINT(1234) * BIGUINT(56) << endl;

    cout << BIGUINT(123) << " / " << BIGUINT(45) << " = " << BIGUINT(123) / BIGUINT(45) << endl;
    cout << BIGUINT(1234567) << " / " << BIGUINT(8901) << " = " << BIGUINT(1234567) / BIGUINT(8901) << endl;

    cout << BIGUINT(123) << " % " << BIGUINT(45) << " = " << BIGUINT(123) % BIGUINT(45) << endl;
    cout << BIGUINT(1234567) << " % " << BIGUINT(8901) << " = " << BIGUINT(1234567) % BIGUINT(8901) << endl;

    cout << BIGUINT(8901) << " / " << BIGUINT(1234567) << " = " << BIGUINT(8901) / BIGUINT(1234567) << endl;
    cout << BIGUINT(8901) << " % " << BIGUINT(1234567) << " = " << BIGUINT(8901) % BIGUINT(1234567) << endl;

    return 0;
}
