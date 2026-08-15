#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigInt {
    string number;    // Stores the number as a string
    bool isNegative;  // True if number is negative

    // Remove unnecessary leading zeros from the number string
    void removeLeadingZeros() {
        // TODO: Implement this function
        size_t firstNonZero = number.find_first_not_of('0');

        if (firstNonZero != string::npos) {
            number = number.substr(firstNonZero);
        } else {
            number = "0";
        }

        if (number == "0") {
            isNegative = false;
        }
    }

    // Compare absolute values of two BigInts (ignore signs)
    // Returns: 1 if |this| > |other|, 0 if equal, -1 if |this| < |other|
    int compareMagnitude(const BigInt& other) const {
        // TODO: Implement this function
        return 0;
    }

public:
    // Default constructor - initialize to zero
    BigInt() {
        // TODO: Implement this constructor
    }

    // Constructor from 64-bit integer
    BigInt(int64_t value) {
        // TODO: Implement this constructor
    }

    // Constructor from string representation
    BigInt(const string& str) {
        if(str[0]=='-'){
         isNegative=true;
         number=str.substr(1); 
        }else{
            isNegative=false;
            number=str;
        }
        removeLeadingZeros();
    }

    // Copy constructor
    BigInt(const BigInt& other) {
        // TODO: Implement this constructor
		number = other.number;
		isNegative = other.isNegative;
    }

    // Destructor
    ~BigInt() {
        // TODO: Implement if needed
    }

    // Assignment operator
    BigInt& operator=(const BigInt& other) {
        // TODO: Implement this operator
        if (this != &other) {
            number = other.number;
            isNegative = other.isNegative;
		}
        return *this;
    }

    // Unary negation operator (-x)
    BigInt operator-() const {
        BigInt result;
        // TODO: Implement negation logic
		result.number = number;
        if(number != "0")
            result.isNegative = !isNegative;
        else 
			result.isNegative = false;
        return result;
    }

    // Unary plus operator (+x)
    BigInt operator+() const {
        BigInt result;
        result= *this;
       
        return result;
    }

    // Addition assignment operator (x += y)
    BigInt& operator+=(const BigInt& other) {
        // TODO: Implement this operator
       if (isNegative == other.isNegative) {
        string res = "";
        int i = number.length() - 1, j = other.number.length() - 1, carry = 0;
        
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += number[i--] - '0';
            if (j >= 0) sum += other.number[j--] - '0';
            carry = sum / 10;
            res += to_string(sum % 10); 
        }
        reverse(res.begin(), res.end());
        number = res;
       } else {
        int comp = compareMagnitude(other);
        if (comp == 0) {
            number = "0";
            isNegative = false;
        } else {
            string top = (comp > 0) ? number : other.number;
            string bot = (comp > 0) ? other.number : number;
            
            string res = "";
            int i = top.length() - 1, j = bot.length() - 1, borrow = 0;
            
            while (i >= 0) {
                int diff = (top[i--] - '0') - borrow - (j >= 0 ? (bot[j--] - '0') : 0);
                if (diff < 0) { diff += 10; borrow = 1; }
                else borrow = 0;
                res += to_string(diff);
            }
            reverse(res.begin(), res.end());
            number = res;
            if (comp < 0) isNegative = other.isNegative;
        }
    }
    removeLeadingZeros();
        return *this;
    }

    // Subtraction assignment operator (x -= y)
    BigInt& operator-=(const BigInt& other) {
        // TODO: Implement this operator
        return *this;
    }

    // Multiplication assignment operator (x *= y)
    BigInt& operator*=(const BigInt& other) {
       
       if(number=="0"||other.number=="0"){
         number="0";
         isNegative=false;
         return *this;
       }


       isNegative=(isNegative^other.isNegative);

        string top = number;
        string bot = other.number;
        
        vector<int>res((top.length()+bot.length()),0);
        
       for(int i = top.length() - 1;i>=0;i--){
         for(int j = bot.length() - 1;j>=0;j--){
          
                res[i+j+1]+=(top[i]-'0')*(bot[j]-'0');
                
        
            }
        }
        for(int i=res.size()-1;i>0;i--){
            if(res[i]>9){
                res[i-1]+=res[i]/10;
                res[i]%=10;
            }

        }
       string num;
        for(int n:res){
            num+=to_string(n);
        }
        number=num;
        removeLeadingZeros();

        return *this;
    }

    // Division assignment operator (x /= y)
    BigInt& operator/=(const BigInt& other) {
        // TODO: Implement this operator
        if(other.number == "0") {
			throw runtime_error("Division by zero");
        }
        if (number == "0") {
            return *this;
		}
		bool finalSign = (isNegative != other.isNegative);

        BigInt dividend = *this;
        dividend.isNegative = false;

        BigInt divisor = other;
        divisor.isNegative = false;

        if (dividend < divisor) {
            number = "0";
            isNegative = false;
            return *this;
        }

        string quotient = "";
        BigInt current;
        current.number = "0";
        current.isNegative = false;

        for (char digit : dividend.number) {
            if (current.number == "0") {
                current.number = string(1, digit);
            }
            else {
                current.number += digit;
            }

            int count = 0;
            while (!(current < divisor)) {
                current -= divisor;
                count++;
            }

            quotient += to_string(count);
        }
        number = quotient;
        isNegative = finalSign;
        removeLeadingZeros();
        return *this;
    }

    // Modulus assignment operator (x %= y)
    BigInt& operator%=(const BigInt& other) {
        // TODO: Implement this operator
        return *this;
    }

    // Pre-increment operator (++x)
    BigInt& operator++() {
        // TODO: Implement this operator
        return *this;
    }

    // Post-increment operator (x++)
    BigInt operator++(int) {
        BigInt temp;
        // TODO: Implement this operator
        return temp;
    }

    // Pre-decrement operator (--x)
    BigInt& operator--() {
        // TODO: Implement this operator
        return *this;
    }

    // Post-decrement operator (x--)
    BigInt operator--(int) {
        BigInt temp;
        // TODO: Implement this operator
        return temp;
    }

    // Convert BigInt to string representation
    string toString() const {
        // TODO: Implement this function
        return "";
    }

    // Output stream operator (for printing)
    friend ostream& operator<<(ostream& os, const BigInt& num) {
        // TODO: Implement this operator
        return os;
    }

    // Input stream operator (for reading from input)
    friend istream& operator>>(istream& is, BigInt& num) {
        // TODO: Implement this operator
        string str;
    if (is >> str) {
        num = BigInt(str);
    }
        return is;
    }

    // Friend declarations for comparison operators
    friend bool operator==(const BigInt& lhs, const BigInt& rhs);
    friend bool operator<(const BigInt& lhs, const BigInt& rhs);
};

// Binary addition operator (x + y)
BigInt operator+(BigInt lhs, const BigInt& rhs) {
    // TODO: Implement this operator
    lhs += rhs;
return lhs;
}

// Binary subtraction operator (x - y)
BigInt operator-(BigInt lhs, const BigInt& rhs) {
    BigInt result;
    // TODO: Implement this operator
    return result;
}

// Binary multiplication operator (x * y)
BigInt operator*(BigInt lhs, const BigInt& rhs) {
    BigInt result=lhs;
    result*=rhs;
    
    return result;
}

// Binary division operator (x / y)
BigInt operator/(BigInt lhs, const BigInt& rhs) {
    BigInt result;
    // TODO: Implement this operator
    return result;
}

// Binary modulus operator (x % y)
BigInt operator%(BigInt lhs, const BigInt& rhs) {
    BigInt result;
    // TODO: Implement this operator
    return result;
}

// Equality comparison operator (x == y)
bool operator==(const BigInt& lhs, const BigInt& rhs) {
    // TODO: Implement this operator
    if (lhs.isNegative != rhs.isNegative) return false;
return lhs.number == rhs.number;
}

// Inequality comparison operator (x != y)
bool operator!=(const BigInt& lhs, const BigInt& rhs) {
    // TODO: Implement this operator
    return false;
}

// Less-than comparison operator (x < y)
bool operator<(const BigInt& lhs, const BigInt& rhs) {
    // TODO: Implement this operator
    return false;
}

// Less-than-or-equal comparison operator (x <= y)
bool operator<=(const BigInt& lhs, const BigInt& rhs) {
    // TODO: Implement this operator
    return (lhs < rhs) || (lhs == rhs);
}

// Greater-than comparison operator (x > y)
bool operator>(const BigInt& lhs, const BigInt& rhs) {
    // TODO: Implement this operator
    return false;
}

// Greater-than-or-equal comparison operator (x >= y)
bool operator>=(const BigInt& lhs, const BigInt& rhs) {
    // TODO: Implement this operator
    return false;
}

int main() {
    cout << "=== BigInt Class Test Program ===" << endl << endl;
    cout << "NOTE: All functions are currently empty." << endl;
    cout << "Your task is to implement ALL the functions above." << endl;
    cout << "The tests below will work once you implement them correctly." << endl << endl;

    /*
    // Test 1: Constructors and basic output
    cout << "1. Constructors and output:" << endl;
    BigInt a(12345);              // Should create BigInt from integer
    BigInt b("-67890");           // Should create BigInt from string
    BigInt c("0");                // Should handle zero correctly
    BigInt d = a;                 // Should use copy constructor
    cout << "a (from int): " << a << endl;        // Should print "12345"
    cout << "b (from string): " << b << endl;     // Should print "-67890"
    cout << "c (zero): " << c << endl;            // Should print "0"
    cout << "d (copy of a): " << d << endl << endl; // Should print "12345"

    // Test 2: Arithmetic operations
    cout << "2. Arithmetic operations:" << endl;
    cout << "a + b = " << a + b << endl;          // Should calculate 12345 + (-67890)
    cout << "a - b = " << a - b << endl;          // Should calculate 12345 - (-67890)
    cout << "a * b = " << a * b << endl;          // Should calculate 12345 * (-67890)
    cout << "b / a = " << b / a << endl;          // Should calculate (-67890) / 12345
    cout << "a % 100 = " << a % BigInt(100) << endl << endl; // Should calculate 12345 % 100

    // Test 3: Relational operators
    cout << "3. Relational operators:" << endl;
    cout << "a == d: " << (a == d) << endl;       // Should be true (12345 == 12345)
    cout << "a != b: " << (a != b) << endl;       // Should be true (12345 != -67890)
    cout << "a < b: " << (a < b) << endl;         // Should be false (12345 < -67890)
    cout << "a > b: " << (a > b) << endl;         // Should be true (12345 > -67890)
    cout << "c == 0: " << (c == BigInt(0)) << endl << endl; // Should be true (0 == 0)

    // Test 4: Unary operators and increments
    cout << "4. Unary operators and increments:" << endl;
    cout << "-a: " << -a << endl;                 // Should print "-12345"
    cout << "++a: " << ++a << endl;               // Should increment and print "12346"
    cout << "a--: " << a-- << endl;               // Should print "12346" then decrement
    cout << "a after decrement: " << a << endl << endl; // Should print "12345"

    // Test 5: Large number operations
    cout << "5. Large number operations:" << endl;
    BigInt num1("12345678901234567890");
    BigInt num2("98765432109876543210");
    cout << "Very large addition: " << num1 + num2 << endl;
    cout << "Very large multiplication: " << num1 * num2 << endl << endl;

    // Test 6: Edge cases and error handling
    cout << "6. Edge cases:" << endl;
    BigInt zero(0);
    BigInt one(1);
    try {
        BigInt result = one / zero;               // Should throw division by zero error
        cout << "Division by zero succeeded (unexpected)" << endl;
    } catch (const runtime_error& e) {
        cout << "Division by zero correctly threw error: " << e.what() << endl;
    }
    cout << "Multiplication by zero: " << one * zero << endl;        // Should be "0"
    cout << "Negative multiplication: " << BigInt(-5) * BigInt(3) << endl;  // Should be "-15"
    cout << "Negative division: " << BigInt(-10) / BigInt(3) << endl;       // Should be "-3"
    cout << "Negative modulus: " << BigInt(-10) % BigInt(3) << endl;        // Should be "-1"
    */

    return 0;
}