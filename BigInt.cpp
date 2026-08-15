// BigInt
BigInt() {
    number = "0";
    isNegative = false;
}

//>operator
bool operator<(const BigInt& lhs, const BigInt& rhs) {

    if (lhs.isNegative && !rhs.isNegative)
        return true;

    if (!lhs.isNegative && rhs.isNegative)
        return false;

    if (!lhs.isNegative && !rhs.isNegative)
        return lhs.compareMagnitude(rhs) < 0;

    return lhs.compareMagnitude(rhs) > 0;
}

//operator--(int)
BigInt operator--(int) {
    BigInt temp = *this;
    --(*this);
    return temp;
}

//=<operator
bool operator>=(const BigInt& lhs, const BigInt& rhs) {
    return !(lhs < rhs);
}


