#if !defined(__IntNode_H__)
#define __IntNode_H__

#include <string>

class Integer {
public:
    enum Type {
        VAL_BOOLEAN =  1 << 0,
        VAL_INT8 =  1 << 1,
        VAL_INT32 =  1 << 2,
        VAL_UINT32 =  1 << 3,
        VAL_INT64 =  1 << 4,
        VAL_UINT64 =  1 << 5,
    };
    Integer() { Set(0); }
    Integer(const Integer& Integer) { Set(Integer); }
    Integer(long long int Integer) { Set(Integer); }
    Integer(unsigned long long int Integer) { Set(Integer); }
    Integer(int Integer) { Set(Integer); }
    Integer(unsigned int Integer) { Set(Integer); }
    Integer(char Integer) { Set(Integer); }
    Integer(bool Integer) { Set(Integer); }
    ~Integer() {}
    void Set(const Integer& Integer) { mType = Integer.mType; mInteger = Integer.mInteger; }
    void Set(long long int Integer) { mType = Type::VAL_INT64; mInteger.int64 = Integer; }
    void Set(unsigned long long int Integer) { mType = Type::VAL_UINT64; mInteger.uint64 = Integer; }
    void Set(bool Integer) { mType = Type::VAL_BOOLEAN;  mInteger.uint64 = (unsigned long long int)Integer; }
    void Set(int Integer) { mType = Type::VAL_INT32; mInteger.int64 = (long long int)Integer; }
    void Set(unsigned int Integer) { mType = Type::VAL_UINT32; mInteger.uint64 = (unsigned long long int)Integer; }
    void Set(char Integer) { mType = Type::VAL_INT8; mInteger.int64 = (long long int)Integer; }
    bool IsZero() const;
    std::string String();

    Integer operator+(const Integer& rhs);
    Integer operator-(const Integer& rhs);
    Integer operator*(const Integer& rhs);
    Integer operator/(const Integer& rhs);
    Integer operator%(const Integer& rhs);
    Integer operator&&(const Integer& rhs);
    Integer operator||(const Integer& rhs);
    Integer operator==(const Integer& rhs);
    Integer operator!=(const Integer& rhs);
    Integer operator>(const Integer& rhs);
    Integer operator>=(const Integer& rhs);
    Integer operator<(const Integer& rhs);
    Integer operator<=(const Integer& rhs);
    Integer operator&(const Integer& rhs);
    Integer operator^(const Integer& rhs);
    Integer operator|(const Integer& rhs);
    Integer operator<<(const Integer& rhs);
    Integer operator>>(const Integer& rhs);
    Integer operator-();
    Integer operator+();
    Integer operator!();
    Integer operator~();
private:
    //Type HelperType(const Integer& opr1, const Integer& opr2);

    union Content{
        bool boolean;
        char int8;
        int int32;
        unsigned int uint32;
        long long int int64;
        unsigned long long int uint64;
    } mInteger;
    Type mType;    
};


class IntNode {
public:
    enum OPCODE {
        OP_CONST,
        OP_LOGAND,
        OP_LOGOR,
        OP_EQ,
        OP_NE,
        OP_GT,
        OP_GE,
        OP_LT,
        OP_LE,
        OP_AND,
        OP_EXOR,
        OP_OR,
        OP_LSHIFT,
        OP_RSHIFT,
        OP_SUB,
        OP_ADD,
        OP_MUL,
        OP_DIV,
        OP_MOD,
        OP_NEG,
        OP_POS,
        OP_LOGNOT,
        OP_NOT,
        OP_COND,
    }; 

public:
    IntNode(OPCODE op, IntNode* opr1, IntNode* opr2 = nullptr, IntNode* opr3 = nullptr)
        :mOP(op), mOpr1(opr1), mOpr2(opr2), mOpr3(opr3),mInteger()
    {}
    IntNode(long long int Integer)
        :mOP(OPCODE::OP_CONST), mOpr1(nullptr), mOpr2(nullptr), mOpr3(nullptr), mInteger(Integer)
    {}
    IntNode(unsigned long long int Integer)
        :mOP(OPCODE::OP_CONST), mOpr1(nullptr), mOpr2(nullptr), mOpr3(nullptr), mInteger(Integer)
    {}
    IntNode(int Integer)
        :mOP(OPCODE::OP_CONST), mOpr1(nullptr), mOpr2(nullptr), mOpr3(nullptr), mInteger(Integer)
    {}
    IntNode(unsigned int Integer)
        :mOP(OPCODE::OP_CONST), mOpr1(nullptr), mOpr2(nullptr), mOpr3(nullptr), mInteger(Integer)
    {}
    IntNode(char Integer)
        :mOP(OPCODE::OP_CONST), mOpr1(nullptr), mOpr2(nullptr), mOpr3(nullptr), mInteger(Integer)
    {}
    IntNode(bool Integer)
        :mOP(OPCODE::OP_CONST), mOpr1(nullptr), mOpr2(nullptr), mOpr3(nullptr), mInteger(Integer)
    {}
    IntNode(const Integer& Integer)
        :mOP(OPCODE::OP_CONST), mOpr1(nullptr), mOpr2(nullptr), mOpr3(nullptr), mInteger(Integer)
    {}
    ~IntNode() {
        delete mOpr1;
        delete mOpr2;
        delete mOpr3;
    }

    Integer Calculate(class TokenList* list);

private:
    Integer mInteger;
    IntNode* mOpr1;
    IntNode* mOpr2;
    IntNode* mOpr3;
    OPCODE mOP;
};

#endif //! __IntNode_H__