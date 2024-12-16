#include <stdexcept>
#include <sstream>

#include "IntNode.h"
#include "Token.h"

//typedef unsigned long long int uint64_t;
//typedef long long int int64_t;
//typedef unsigned int uint32_t;
//typedef int int32_t;
//typedef char int8_t;

bool Integer::IsZero() const {
    bool ret = true;
    switch(mType) {
        case Integer::Type::VAL_UINT64:
            ret = (mInteger.uint64 == 0);
            break;
        case Integer::Type::VAL_UINT32:
            ret = (mInteger.uint32 == 0);
            break;
        case Integer::Type::VAL_INT64:
            ret = (mInteger.int64 == 0);
            break;
        case Integer::Type::VAL_INT32:
            ret = (mInteger.int32 == 0);
            break;
        case Integer::Type::VAL_INT8:
            ret = (mInteger.int8 == 0);
            break;
        case Integer::Type::VAL_BOOLEAN:
            ret = (mInteger.boolean == 0);
            break;
        default:
            break;
    }
    return ret;
}

std::string Integer::String() {
    std::stringstream ss;
    switch(mType) {
        case Integer::Type::VAL_UINT64:
            ss << mInteger.uint64 << "ULL";
            break;
        case Integer::Type::VAL_UINT32:
            ss << mInteger.uint32 << "UL";
            break;
        case Integer::Type::VAL_INT64:
            ss << mInteger.int64 << "LL";
            break;
        case Integer::Type::VAL_INT32:
            ss << mInteger.int32;
            break;
        case Integer::Type::VAL_INT8: {
            ss << '\'';
            switch(mInteger.int8) {
                case '\a':  ss << "\\a"; break;
                case '\b':  ss << "\\b"; break;
                case '\f':  ss << "\\f"; break;
                case '\n':  ss << "\\n"; break;
                case '\r':  ss << "\\r"; break;
                case '\t':  ss << "\\t"; break;
                case '\0':  ss << "\\0"; break;
                case '\'':  ss << "\\\""; break;
                case '\\':  ss << "\\\\"; break;
                default:    ss << mInteger.int8; break;
            }      
            ss << '\'';      
        }
            break;
        case Integer::Type::VAL_BOOLEAN:
            ss << mInteger.boolean;
            break;
        default:
            ss << "";
            break;
    }
    return ss.str();
}

Integer Integer::operator+(const Integer& rhs) {
    Integer ret;
    int type = mType | rhs.mType;

    if(type & Integer::Type::VAL_UINT64) {
        ret.Set(mInteger.uint64 + rhs.mInteger.uint64);
    } else if(type & Integer::Type::VAL_INT64) {
        ret.Set(mInteger.int64 + rhs.mInteger.int64);
    } else if(type & Integer::Type::VAL_UINT32) {
        ret.Set(mInteger.uint32 + rhs.mInteger.uint32);
    } else if(type & Integer::Type::VAL_INT32) {
        ret.Set(mInteger.int32 + rhs.mInteger.int32);
    } else if(type & Integer::Type::VAL_INT8) {
        ret.Set(mInteger.int8 + rhs.mInteger.int8);
    } else if(type & Integer::Type::VAL_BOOLEAN) {
        ret.Set(mInteger.boolean + rhs.mInteger.boolean);
    } 

    return ret;
#if(0)
    switch(rhs.mType) {
        case Integer::Type::VAL_UINT64:
            ret.Set(Integer::Type::VAL_UINT64, (uint64_t)(mInteger.uval) + (uint64_t)(rhs.mInteger.uval));
            break;
        case Integer::Type::VAL_INT64:
            switch(rhs.mType) {
                case Integer::Type::VAL_UINT64:
                    ret.Set(Integer::Type::VAL_UINT64, (uint64_t)(mInteger.ival) + (uint64_t)(rhs.mInteger.uval));
                    break;
                case Integer::Type::VAL_INT64:
                    ret.Set(Integer::Type::VAL_INT64, (int64_t)(mInteger.ival) + (int64_t)(rhs.mInteger.ival));
                    break;
                default:
                    ret.Set(Integer::Type::VAL_INT64, (int64_t)(mInteger.ival) + (int64_t)(rhs.mInteger.ival));
                    break;
            }
            break;
        case Integer::Type::VAL_UINT32:
            switch(rhs.mType) {
                case Integer::Type::VAL_UINT64:
                    ret.Set(Integer::Type::VAL_UINT64, (uint64_t)(mInteger.ival) + (uint64_t)(rhs.mInteger.uval));
                    break;
                case Integer::Type::VAL_INT64:
                    ret.Set(Integer::Type::VAL_INT64, (int64_t)(mInteger.ival) + (int64_t)(rhs.mInteger.ival));
                    break;
                case Integer::Type::VAL_UINT32:
                case Integer::Type::VAL_INT32:
                case Integer::Type::VAL_INT8:
                case Integer::Type::VAL_BOOLEAN:
                default:
            }
            break;
        case Integer::Type::VAL_INT32:
            switch(rhs.mType) {
                case Integer::Type::VAL_UINT64:
                case Integer::Type::VAL_INT64:
                case Integer::Type::VAL_UINT32:
                case Integer::Type::VAL_INT32:
                case Integer::Type::VAL_INT8:
                case Integer::Type::VAL_BOOLEAN:
                default:
            }
            break;
        case Integer::Type::VAL_INT8:
            switch(rhs.mType) {
                case Integer::Type::VAL_UINT64:
                case Integer::Type::VAL_INT64:
                case Integer::Type::VAL_UINT32:
                case Integer::Type::VAL_INT32:
                case Integer::Type::VAL_INT8:
                case Integer::Type::VAL_BOOLEAN:
                default:
            }
            break;
        case Integer::Type::VAL_BOOLEAN:
            switch(rhs.mType) {
                case Integer::Type::VAL_UINT64:
                case Integer::Type::VAL_INT64:
                case Integer::Type::VAL_UINT32:
                case Integer::Type::VAL_INT32:
                case Integer::Type::VAL_INT8:
                case Integer::Type::VAL_BOOLEAN:
                default:
            }
            break;
        default:
    }
#endif
}

Integer Integer::operator-(const Integer& rhs) {
    Integer ret;
    int type = mType | rhs.mType;

    if(type & Integer::Type::VAL_UINT64) {
        ret.Set(mInteger.uint64 - rhs.mInteger.uint64);
    } else if(type & Integer::Type::VAL_INT64) {
        ret.Set(mInteger.int64 - rhs.mInteger.int64);
    } else if(type & Integer::Type::VAL_UINT32) {
        ret.Set(mInteger.uint32 - rhs.mInteger.uint32);
    } else if(type & Integer::Type::VAL_INT32) {
        ret.Set(mInteger.int32 - rhs.mInteger.int32);
    } else if(type & Integer::Type::VAL_INT8) {
        ret.Set(mInteger.int8 - rhs.mInteger.int8);
    } else if(type & Integer::Type::VAL_BOOLEAN) {
        ret.Set(mInteger.boolean - rhs.mInteger.boolean);
    } 

    return ret;
}

Integer Integer::operator*(const Integer& rhs) {
    Integer ret;
    int type = mType | rhs.mType;

    if(type & Integer::Type::VAL_UINT64) {
        ret.Set(mInteger.uint64 * rhs.mInteger.uint64);
    } else if(type & Integer::Type::VAL_INT64) {
        ret.Set(mInteger.int64 * rhs.mInteger.int64);
    } else if(type & Integer::Type::VAL_UINT32) {
        ret.Set(mInteger.uint32 * rhs.mInteger.uint32);
    } else if(type & Integer::Type::VAL_INT32) {
        ret.Set(mInteger.int32 * rhs.mInteger.int32);
    } else if(type & Integer::Type::VAL_INT8) {
        ret.Set(mInteger.int8 * rhs.mInteger.int8);
    } else if(type & Integer::Type::VAL_BOOLEAN) {
        ret.Set(mInteger.boolean + rhs.mInteger.boolean);
    } 

    return ret;
}

Integer Integer::operator/(const Integer& rhs) {
    if(rhs.IsZero()){
        throw std::runtime_error("zero divide error");
    }
    Integer ret;
    int type = mType | rhs.mType;

    if(type & Integer::Type::VAL_UINT64) {
        ret.Set(mInteger.uint64 / rhs.mInteger.uint64);
    } else if(type & Integer::Type::VAL_INT64) {
        ret.Set(mInteger.int64 / rhs.mInteger.int64);
    } else if(type & Integer::Type::VAL_UINT32) {
        ret.Set(mInteger.uint32 / rhs.mInteger.uint32);
    } else if(type & Integer::Type::VAL_INT32) {
        ret.Set(mInteger.int32 / rhs.mInteger.int32);
    } else if(type & Integer::Type::VAL_INT8) {
        ret.Set(mInteger.int8 / rhs.mInteger.int8);
    } else if(type & Integer::Type::VAL_BOOLEAN) {
        ret.Set(mInteger.boolean / rhs.mInteger.boolean);
    } 

    return ret;
}

Integer Integer::operator%(const Integer& rhs) {
    if(rhs.IsZero()){
        throw std::runtime_error("zero divide error");
    }
    Integer ret;
    int type = mType | rhs.mType;

    if(type & Integer::Type::VAL_UINT64) {
        ret.Set(mInteger.uint64 % rhs.mInteger.uint64);
    } else if(type & Integer::Type::VAL_INT64) {
        ret.Set(mInteger.int64 % rhs.mInteger.int64);
    } else if(type & Integer::Type::VAL_UINT32) {
        ret.Set(mInteger.uint32 % rhs.mInteger.uint32);
    } else if(type & Integer::Type::VAL_INT32) {
        ret.Set(mInteger.int32 % rhs.mInteger.int32);
    } else if(type & Integer::Type::VAL_INT8) {
        ret.Set(mInteger.int8 % rhs.mInteger.int8);
    } else if(type & Integer::Type::VAL_BOOLEAN) {
        ret.Set(mInteger.boolean % rhs.mInteger.boolean);
    } 

    return ret;
}

Integer Integer::operator&&(const Integer& rhs) {
    Integer ret;
    int type = mType | rhs.mType;

    if(type & Integer::Type::VAL_UINT64) {
        ret.Set(mInteger.uint64 && rhs.mInteger.uint64);
    } else if(type & Integer::Type::VAL_INT64) {
        ret.Set(mInteger.int64 && rhs.mInteger.int64);
    } else if(type & Integer::Type::VAL_UINT32) {
        ret.Set(mInteger.uint32 && rhs.mInteger.uint32);
    } else if(type & Integer::Type::VAL_INT32) {
        ret.Set(mInteger.int32 && rhs.mInteger.int32);
    } else if(type & Integer::Type::VAL_INT8) {
        ret.Set(mInteger.int8 && rhs.mInteger.int8);
    } else if(type & Integer::Type::VAL_BOOLEAN) {
        ret.Set(mInteger.boolean && rhs.mInteger.boolean);
    } 

    return ret;
}

Integer Integer::operator||(const Integer& rhs) {
    Integer ret;
    int type = mType | rhs.mType;

    if(type & Integer::Type::VAL_UINT64) {
        ret.Set(mInteger.uint64 || rhs.mInteger.uint64);
    } else if(type & Integer::Type::VAL_INT64) {
        ret.Set(mInteger.int64 || rhs.mInteger.int64);
    } else if(type & Integer::Type::VAL_UINT32) {
        ret.Set(mInteger.uint32 || rhs.mInteger.uint32);
    } else if(type & Integer::Type::VAL_INT32) {
        ret.Set(mInteger.int32 || rhs.mInteger.int32);
    } else if(type & Integer::Type::VAL_INT8) {
        ret.Set(mInteger.int8 || rhs.mInteger.int8);
    } else if(type & Integer::Type::VAL_BOOLEAN) {
        ret.Set(mInteger.boolean || rhs.mInteger.boolean);
    } 

    return ret;
}

Integer Integer::operator==(const Integer& rhs) {
    Integer ret;
    int type = mType | rhs.mType;

    if(type & Integer::Type::VAL_UINT64) {
        ret.Set(mInteger.uint64 == rhs.mInteger.uint64);
    } else if(type & Integer::Type::VAL_INT64) {
        ret.Set(mInteger.int64 == rhs.mInteger.int64);
    } else if(type & Integer::Type::VAL_UINT32) {
        ret.Set(mInteger.uint32 == rhs.mInteger.uint32);
    } else if(type & Integer::Type::VAL_INT32) {
        ret.Set(mInteger.int32 == rhs.mInteger.int32);
    } else if(type & Integer::Type::VAL_INT8) {
        ret.Set(mInteger.int8 == rhs.mInteger.int8);
    } else if(type & Integer::Type::VAL_BOOLEAN) {
        ret.Set(mInteger.boolean == rhs.mInteger.boolean);
    } 

    return ret;
}

Integer Integer::operator!=(const Integer& rhs) {
    Integer ret;
    int type = mType | rhs.mType;

    if(type & Integer::Type::VAL_UINT64) {
        ret.Set(mInteger.uint64 != rhs.mInteger.uint64);
    } else if(type & Integer::Type::VAL_INT64) {
        ret.Set(mInteger.int64 != rhs.mInteger.int64);
    } else if(type & Integer::Type::VAL_UINT32) {
        ret.Set(mInteger.uint32 != rhs.mInteger.uint32);
    } else if(type & Integer::Type::VAL_INT32) {
        ret.Set(mInteger.int32 != rhs.mInteger.int32);
    } else if(type & Integer::Type::VAL_INT8) {
        ret.Set(mInteger.int8 != rhs.mInteger.int8);
    } else if(type & Integer::Type::VAL_BOOLEAN) {
        ret.Set(mInteger.boolean != rhs.mInteger.boolean);
    } 

    return ret;
}

Integer Integer::operator>(const Integer& rhs) {
    Integer ret;
    int type = mType | rhs.mType;

    if(type & Integer::Type::VAL_UINT64) {
        ret.Set(mInteger.uint64 > rhs.mInteger.uint64);
    } else if(type & Integer::Type::VAL_INT64) {
        ret.Set(mInteger.int64 > rhs.mInteger.int64);
    } else if(type & Integer::Type::VAL_UINT32) {
        ret.Set(mInteger.uint32 > rhs.mInteger.uint32);
    } else if(type & Integer::Type::VAL_INT32) {
        ret.Set(mInteger.int32 > rhs.mInteger.int32);
    } else if(type & Integer::Type::VAL_INT8) {
        ret.Set(mInteger.int8 > rhs.mInteger.int8);
    } else if(type & Integer::Type::VAL_BOOLEAN) {
        ret.Set(mInteger.boolean > rhs.mInteger.boolean);
    } 

    return ret;
}

Integer Integer::operator>=(const Integer& rhs) {
    Integer ret;
    int type = mType | rhs.mType;

    if(type & Integer::Type::VAL_UINT64) {
        ret.Set(mInteger.uint64 >= rhs.mInteger.uint64);
    } else if(type & Integer::Type::VAL_INT64) {
        ret.Set(mInteger.int64 >= rhs.mInteger.int64);
    } else if(type & Integer::Type::VAL_UINT32) {
        ret.Set(mInteger.uint32 >= rhs.mInteger.uint32);
    } else if(type & Integer::Type::VAL_INT32) {
        ret.Set(mInteger.int32 >= rhs.mInteger.int32);
    } else if(type & Integer::Type::VAL_INT8) {
        ret.Set(mInteger.int8 >= rhs.mInteger.int8);
    } else if(type & Integer::Type::VAL_BOOLEAN) {
        ret.Set(mInteger.boolean >= rhs.mInteger.boolean);
    } 

    return ret;
}

Integer Integer::operator<(const Integer& rhs) {
    Integer ret;
    int type = mType | rhs.mType;

    if(type & Integer::Type::VAL_UINT64) {
        ret.Set(mInteger.uint64 < rhs.mInteger.uint64);
    } else if(type & Integer::Type::VAL_INT64) {
        ret.Set(mInteger.int64 < rhs.mInteger.int64);
    } else if(type & Integer::Type::VAL_UINT32) {
        ret.Set(mInteger.uint32 < rhs.mInteger.uint32);
    } else if(type & Integer::Type::VAL_INT32) {
        ret.Set(mInteger.int32 < rhs.mInteger.int32);
    } else if(type & Integer::Type::VAL_INT8) {
        ret.Set(mInteger.int8 < rhs.mInteger.int8);
    } else if(type & Integer::Type::VAL_BOOLEAN) {
        ret.Set(mInteger.boolean < rhs.mInteger.boolean);
    } 

    return ret;
}

Integer Integer::operator<=(const Integer& rhs) {
    Integer ret;
    int type = mType | rhs.mType;

    if(type & Integer::Type::VAL_UINT64) {
        ret.Set(mInteger.uint64 <= rhs.mInteger.uint64);
    } else if(type & Integer::Type::VAL_INT64) {
        ret.Set(mInteger.int64 <= rhs.mInteger.int64);
    } else if(type & Integer::Type::VAL_UINT32) {
        ret.Set(mInteger.uint32 <= rhs.mInteger.uint32);
    } else if(type & Integer::Type::VAL_INT32) {
        ret.Set(mInteger.int32 <= rhs.mInteger.int32);
    } else if(type & Integer::Type::VAL_INT8) {
        ret.Set(mInteger.int8 <= rhs.mInteger.int8);
    } else if(type & Integer::Type::VAL_BOOLEAN) {
        ret.Set(mInteger.boolean <= rhs.mInteger.boolean);
    } 

    return ret;
}

Integer Integer::operator&(const Integer& rhs) {
    Integer ret;
    int type = mType | rhs.mType;

    if(type & Integer::Type::VAL_UINT64) {
        ret.Set(mInteger.uint64 & rhs.mInteger.uint64);
    } else if(type & Integer::Type::VAL_INT64) {
        ret.Set(mInteger.int64 & rhs.mInteger.int64);
    } else if(type & Integer::Type::VAL_UINT32) {
        ret.Set(mInteger.uint32 & rhs.mInteger.uint32);
    } else if(type & Integer::Type::VAL_INT32) {
        ret.Set(mInteger.int32 & rhs.mInteger.int32);
    } else if(type & Integer::Type::VAL_INT8) {
        ret.Set(mInteger.int8 & rhs.mInteger.int8);
    } else if(type & Integer::Type::VAL_BOOLEAN) {
        ret.Set(mInteger.boolean & rhs.mInteger.boolean);
    } 

    return ret;
}

Integer Integer::operator^(const Integer& rhs) {
    Integer ret;
    int type = mType | rhs.mType;

    if(type & Integer::Type::VAL_UINT64) {
        ret.Set(mInteger.uint64 ^ rhs.mInteger.uint64);
    } else if(type & Integer::Type::VAL_INT64) {
        ret.Set(mInteger.int64 ^ rhs.mInteger.int64);
    } else if(type & Integer::Type::VAL_UINT32) {
        ret.Set(mInteger.uint32 ^ rhs.mInteger.uint32);
    } else if(type & Integer::Type::VAL_INT32) {
        ret.Set(mInteger.int32 ^ rhs.mInteger.int32);
    } else if(type & Integer::Type::VAL_INT8) {
        ret.Set(mInteger.int8 ^ rhs.mInteger.int8);
    } else if(type & Integer::Type::VAL_BOOLEAN) {
        ret.Set(mInteger.boolean ^ rhs.mInteger.boolean);
    } 

    return ret;
}

Integer Integer::operator|(const Integer& rhs) {
    Integer ret;
    int type = mType | rhs.mType;

    if(type & Integer::Type::VAL_UINT64) {
        ret.Set(mInteger.uint64 | rhs.mInteger.uint64);
    } else if(type & Integer::Type::VAL_INT64) {
        ret.Set(mInteger.int64 | rhs.mInteger.int64);
    } else if(type & Integer::Type::VAL_UINT32) {
        ret.Set(mInteger.uint32 | rhs.mInteger.uint32);
    } else if(type & Integer::Type::VAL_INT32) {
        ret.Set(mInteger.int32 | rhs.mInteger.int32);
    } else if(type & Integer::Type::VAL_INT8) {
        ret.Set(mInteger.int8 | rhs.mInteger.int8);
    } else if(type & Integer::Type::VAL_BOOLEAN) {
        ret.Set(mInteger.boolean | rhs.mInteger.boolean);
    } 

    return ret;
}

Integer Integer::operator<<(const Integer& rhs) {
    Integer ret;
    int type = mType | rhs.mType;

    if(type & Integer::Type::VAL_UINT64) {
        ret.Set(mInteger.uint64 << rhs.mInteger.uint64);
    } else if(type & Integer::Type::VAL_INT64) {
        ret.Set(mInteger.int64 << rhs.mInteger.int64);
    } else if(type & Integer::Type::VAL_UINT32) {
        ret.Set(mInteger.uint32 << rhs.mInteger.uint32);
    } else if(type & Integer::Type::VAL_INT32) {
        ret.Set(mInteger.int32 << rhs.mInteger.int32);
    } else if(type & Integer::Type::VAL_INT8) {
        ret.Set(mInteger.int8 << rhs.mInteger.int8);
    } else if(type & Integer::Type::VAL_BOOLEAN) {
        ret.Set(mInteger.boolean << rhs.mInteger.boolean);
    } 

    return ret;
}

Integer Integer::operator>>(const Integer& rhs) {
    Integer ret;
    int type = mType | rhs.mType;

    if(type & Integer::Type::VAL_UINT64) {
        ret.Set(mInteger.uint64 >> rhs.mInteger.uint64);
    } else if(type & Integer::Type::VAL_INT64) {
        ret.Set(mInteger.int64 >> rhs.mInteger.int64);
    } else if(type & Integer::Type::VAL_UINT32) {
        ret.Set(mInteger.uint32 >> rhs.mInteger.uint32);
    } else if(type & Integer::Type::VAL_INT32) {
        ret.Set(mInteger.int32 >> rhs.mInteger.int32);
    } else if(type & Integer::Type::VAL_INT8) {
        ret.Set(mInteger.int8 >> rhs.mInteger.int8);
    } else if(type & Integer::Type::VAL_BOOLEAN) {
        ret.Set(mInteger.boolean >> rhs.mInteger.boolean);
    } 

    return ret;
}

Integer Integer::operator-() {
    Integer ret;
    
    if(mType & Integer::Type::VAL_UINT64) {
        ret.Set(-(mInteger.uint64));
    } else if(mType & Integer::Type::VAL_INT64) {
        ret.Set(-(mInteger.int64));
    } else if(mType & Integer::Type::VAL_UINT32) {
        ret.Set(-(mInteger.uint32));
    } else if(mType & Integer::Type::VAL_INT32) {
        ret.Set(-(mInteger.int32));
    } else if(mType & Integer::Type::VAL_INT8) {
        ret.Set(-(mInteger.int8));
    } else if(mType & Integer::Type::VAL_BOOLEAN) {
        ret.Set(-(mInteger.boolean));
    } 

    return ret;
}

Integer Integer::operator+() {
    Integer ret;
    
    if(mType & Integer::Type::VAL_UINT64) {
        ret.Set(+(mInteger.uint64));
    } else if(mType & Integer::Type::VAL_INT64) {
        ret.Set(+(mInteger.int64));
    } else if(mType & Integer::Type::VAL_UINT32) {
        ret.Set(+(mInteger.uint32));
    } else if(mType & Integer::Type::VAL_INT32) {
        ret.Set(+(mInteger.int32));
    } else if(mType & Integer::Type::VAL_INT8) {
        ret.Set(+(mInteger.int8));
    } else if(mType & Integer::Type::VAL_BOOLEAN) {
        ret.Set(+(mInteger.boolean));
    } 

    return ret;
}

Integer Integer::operator!() {
    Integer ret;
    
    if(mType & Integer::Type::VAL_UINT64) {
        ret.Set(!(mInteger.uint64));
    } else if(mType & Integer::Type::VAL_INT64) {
        ret.Set(!(mInteger.int64));
    } else if(mType & Integer::Type::VAL_UINT32) {
        ret.Set(!(mInteger.uint32));
    } else if(mType & Integer::Type::VAL_INT32) {
        ret.Set(!(mInteger.int32));
    } else if(mType & Integer::Type::VAL_INT8) {
        ret.Set(!(mInteger.int8));
    } else if(mType & Integer::Type::VAL_BOOLEAN) {
        ret.Set(!(mInteger.boolean));
    } 

    return ret;
}

Integer Integer::operator~() {
    Integer ret;
    
    if(mType & Integer::Type::VAL_UINT64) {
        ret.Set(~(mInteger.uint64));
    } else if(mType & Integer::Type::VAL_INT64) {
        ret.Set(~(mInteger.int64));
    } else if(mType & Integer::Type::VAL_UINT32) {
        ret.Set(~(mInteger.uint32));
    } else if(mType & Integer::Type::VAL_INT32) {
        ret.Set(~(mInteger.int32));
    } else if(mType & Integer::Type::VAL_INT8) {
        ret.Set(~(mInteger.int8));
    } else if(mType & Integer::Type::VAL_BOOLEAN) {
        ret.Set(~(mInteger.boolean));
    } 

    return ret;
}
/*
Integer::Type Integer::HelperType(const Integer& opr1, const Integer& opr2) {
    if(opr1.type == opr2.type)
        return opr1.type;
    
    switch(opr1.type) {
        case Integer::Type::VAL_UINT64:
            return opr1.type;
        case Integer::Type::VAL_INT64:
            switch(opr2.type) {
                case Integer::Type::VAL_UINT64: 
                    return opr2.type;
                default:
                    return opr1.type;
            }
        case Integer::Type::VAL_UINT32:
            switch(opr2.type) {
                case Integer::Type::VAL_UINT64: 
                case Integer::Type::VAL_INT64:
                    return opr2.type;
                default:
                    return opr1.type;
            }
        case Integer::Type::VAL_INT32:
            switch(opr2.type) {
                case Integer::Type::VAL_UINT64: 
                case Integer::Type::VAL_INT64:
                case Integer::Type::VAL_UINT32:
                    return opr2.type;
                default:
                    return opr1.type;
            }
        case Integer::Type::VAL_INT8:
            switch(opr2.type) {
                case Integer::Type::VAL_UINT64: 
                case Integer::Type::VAL_INT64:
                case Integer::Type::VAL_UINT32:
                case Integer::Type::VAL_INT32:
                    return opr2.type;
                default:
                    return opr1.type;
            }
        case Integer::Type::VAL_BOOLEAN:
            return opr2.type;
        default:
            return Integer::Type::VAL_INT32;
    }
}

*/


Integer IntNode::Calculate(TokenList* list) {
    Integer ret;
    if(mOP == OPCODE::OP_CONST) {
        return mInteger;
    } else if(mOpr3 != nullptr) {
        switch(mOP) {
            case OPCODE::OP_COND:
                ret = !mOpr1->Calculate(list).IsZero() ? mOpr2->Calculate(list) : mOpr3->Calculate(list);
                break;
        }
    } else if(mOpr2 == nullptr) {
        switch(mOP) {
            case OPCODE::OP_NEG:      ret = - mOpr1->Calculate(list); break;
            case OPCODE::OP_POS:      ret = + mOpr1->Calculate(list); break;
            case OPCODE::OP_LOGNOT:   ret = ! mOpr1->Calculate(list); break;
            case OPCODE::OP_NOT:      ret = ~ mOpr1->Calculate(list); break;
        }
    } else {
        switch(mOP) {
            case OPCODE::OP_LOGAND:   ret = mOpr1->Calculate(list) && mOpr2->Calculate(list); break;
            case OPCODE::OP_LOGOR:    ret = mOpr1->Calculate(list) || mOpr2->Calculate(list); break;
            case OPCODE::OP_EQ:       ret = mOpr1->Calculate(list) == mOpr2->Calculate(list); break;
            case OPCODE::OP_NE:       ret = mOpr1->Calculate(list) != mOpr2->Calculate(list); break;
            case OPCODE::OP_GT:       ret = mOpr1->Calculate(list) > mOpr2->Calculate(list); break;
            case OPCODE::OP_GE:       ret = mOpr1->Calculate(list) >= mOpr2->Calculate(list); break;
            case OPCODE::OP_LT:       ret = mOpr1->Calculate(list) < mOpr2->Calculate(list); break;
            case OPCODE::OP_LE:       ret = mOpr1->Calculate(list) <= mOpr2->Calculate(list); break;
            case OPCODE::OP_AND:      ret = mOpr1->Calculate(list) & mOpr2->Calculate(list); break;
            case OPCODE::OP_EXOR:     ret = mOpr1->Calculate(list) ^ mOpr2->Calculate(list); break;
            case OPCODE::OP_OR:       ret = mOpr1->Calculate(list) | mOpr2->Calculate(list); break;
            case OPCODE::OP_LSHIFT:   ret = mOpr1->Calculate(list) << mOpr2->Calculate(list); break;
            case OPCODE::OP_RSHIFT:   ret = mOpr1->Calculate(list) >> mOpr2->Calculate(list); break;
            case OPCODE::OP_SUB:      ret = mOpr1->Calculate(list) - mOpr2->Calculate(list); break;
            case OPCODE::OP_ADD:      ret = mOpr1->Calculate(list) + mOpr2->Calculate(list); break;
            case OPCODE::OP_MUL:      ret = mOpr1->Calculate(list) * mOpr2->Calculate(list); break;
            case OPCODE::OP_DIV: {
                try {
                    ret = mOpr1->Calculate(list) / mOpr2->Calculate(list); 
                } catch (const std::exception &e) {
                    list->Error(0,0, e.what());
                }
                break;
            }      
            case OPCODE::OP_MOD: {
                try {
                    ret = mOpr1->Calculate(list) % mOpr2->Calculate(list); 
                } catch (const std::exception &e) {
                    list->Error(0,0, e.what());
                }
                break;
            }
        }
    }

    return ret;
}