#include <climits>
#include <cmath>
#include "tritset"

static size_t calculate_size(size_t size){
    return ceil(static_cast<double> (size) / (static_cast<double>(sizeof(unsigned int)) * CHAR_BIT / 2));
}


static size_t calculate_shift(size_t index){
    return ((index + 1) % (sizeof(unsigned int) * CHAR_BIT / 2) - 1) * 2;
}


static Trit neg(Trit value){
    if (value == True) return False;
    if (value == False) return True;
    return Unknown;
}


static Trit disj(Trit value1, Trit value2){
    if (value1 == True || value2 == True) return True;
    if (value1 == False && value2 == False) return False;
    return Unknown;
}


static Trit konj(Trit value1, Trit value2){
    if (value1 == False || value2 == False) return False;
    if (value1 == True && value2 == True) return True;
    return Unknown;
}


TritSet::TritSet(const size_t & size) {
    size_t length = calculate_size(size);
    set = vector <unsigned int> (length);

    trits_count = size;

    for (size_t i = 0; i < size; ++i)
        (*this)[i] = Unknown;
}


size_t TritSet::capacity() const {
    return ceil(static_cast<double>(trits_count) / (static_cast<double>(sizeof(unsigned int)) * CHAR_BIT / 2));
}


size_t TritSet::cardinality(Trit value){
    size_t length = this->trits_count;
    size_t count = 0;
    if (value == Unknown){
        for (size_t i = length - 1; i > 0; --i) {
            ++count;
            if (!((*this)[i] == Unknown)) break;
        }
        count = length - count;
    }
    else for (size_t i = 0; i < length; ++i) {
        if ((*this)[i] == value) ++count;
    }

    return count;
}


unordered_map <Trit, int, hash <int>> TritSet::cardinality(){
    unordered_map <Trit, int, hash <int>> map;

    map[Unknown] = this->cardinality(Unknown);
    map[False] = this->cardinality(False);
    map[True] = this->cardinality(True);

    return map;
}


void TritSet::trim(size_t lastIndex){
    size_t length = this->trits_count;

    for (size_t i = lastIndex + 1; i < length; ++i)
        (*this)[i] = Unknown;
};


size_t TritSet::length(){
    size_t length = this->trits_count;

    size_t logical_len = 0;

    for (size_t i = 0; i < length; ++i)
        if (!((*this)[i] == Unknown)) logical_len = i;

    return logical_len + 1;
}


TritSet::ProxyTritSet::ProxyTritSet(TritSet &set, size_t index) : set(set), index(index){}


TritSet::ProxyTritSet & TritSet::ProxyTritSet::resize(size_t new_size) {
    size_t new_length = calculate_size(new_size);
    set.set.resize(new_length);

    size_t old_num_trits = set.trits_count;

    set.trits_count = new_size;

    for (size_t i = old_num_trits; i < new_size; ++i)
        set[i] = Unknown;

    return *this;
}


enum Trit TritSet::ProxyTritSet::get_trit() const {
    size_t index_uint = calculate_size(index + 1) - 1;

    unsigned int shift = calculate_shift(index);

    unsigned int mask = ((unsigned)3 << shift);

    unsigned int trit = (mask & this->set.set[index_uint]) >> shift;

    return (Trit)trit;
}


TritSet::ProxyTritSet & TritSet::ProxyTritSet::operator = (Trit value) {
    if (index < set.trits_count || value != Unknown){
        if ((value != Unknown) && (index >= set.trits_count)) this->resize(index + 1);

        size_t index_uint = calculate_size(index + 1) - 1;

        unsigned int shift = calculate_shift(index);

        unsigned int mask1 = ~((unsigned)3 << shift);
        set.set[index_uint] &= mask1;

        unsigned int mask2 = (unsigned)value << shift;
        set.set[index_uint] |= mask2;
    }
    return *this;
}


Trit TritSet::ProxyTritSet::operator~() {
    if (this->index < this->set.trits_count){
        size_t index_uint = calculate_size(index + 1) - 1;

        unsigned int shift = calculate_shift(index);

        unsigned int mask = ((unsigned)3 << shift);

        unsigned int trit = ((mask & this->set.set[index_uint]) >> shift);

        return neg((Trit)(trit));
    }
    return Unknown;
}


Trit TritSet::ProxyTritSet::operator | (const TritSet::ProxyTritSet &set2){
    if (this->index < this->set.trits_count && set2.index < set2.set.trits_count) {
        unsigned int trit1 = this->get_trit();
        unsigned int trit2 = set2.get_trit();

        Trit result = disj((Trit)trit1, (Trit)trit2);

        return result;
    }
    return Unknown;
}


Trit TritSet::ProxyTritSet::operator & (const TritSet::ProxyTritSet &set2) {
    if (this->index < this->set.trits_count && set2.index < set2.set.trits_count) {
        unsigned int trit1 = this->get_trit();
        unsigned int trit2 = set2.get_trit();

        Trit result = konj((Trit)trit1, (Trit)trit2);

        return result;
    }
    return Unknown;
}


bool TritSet::ProxyTritSet::operator==(Trit value) {
    if (index < set.trits_count){
        size_t index_uint = calculate_size(index + 1) - 1;

        unsigned int shift = calculate_shift(index);

        unsigned int mask = ((unsigned)3 << shift);

        unsigned int result = (mask & set.set[index_uint]) >> shift;

        return (result == value);
    }
    return (Unknown == value);
}


TritSet TritSet::operator~() {
    TritSet new_set(this->trits_count);
    size_t new_size = this->trits_count;
    for (size_t i = 0; i < new_size; ++i)
        new_set[i] = ~(*this)[i];
    return new_set;
}


TritSet TritSet::operator | (TritSet &set1) {
    size_t max = this->trits_count, min = set1.trits_count;
    TritSet *max_set = this;
    if (set1.trits_count > this->trits_count) {
        max = set1.trits_count;
        min = this->trits_count;
        max_set = &(set1);
    }

    TritSet new_set(max);

    for (size_t i = 0; i < min; ++i)
        new_set[i] = (*this)[i] | set1[i];

    for (size_t i = min; i < max; ++i)
        new_set[i] = new_set[i] | (*max_set)[i];

    return new_set;
}


TritSet TritSet::operator&(TritSet &set1){
    size_t max = this->trits_count, min = set1.trits_count;
    TritSet *max_set = this;
    if (set1.trits_count > this->trits_count) {
        max = set1.trits_count;
        min = this->trits_count;
        max_set = &(set1);
    }

    TritSet new_set(max);

    for (size_t i = 0; i < min; ++i)
        new_set[i] = (*this)[i] & set1[i];

    for (size_t i = min; i < max; ++i)
        new_set[i] = new_set[i] & (*max_set)[i];

    return new_set;
}


TritSet::ProxyTritSet TritSet::operator[](size_t index) {
    return (ProxyTritSet(*this, index));
}
