//
// Created by yangkeao on 6/11/19.
//

#ifndef HALIDE_CONST_H
#define HALIDE_CONST_H


#include "Expr.h"

namespace Halide {
    class Const : public Expr {
    };

    class ConstInt : public Const {
      private:
        int value;
      public:
        ConstInt(int value);
    };

    class ConstUInt : public Const {
      private:
        unsigned int value;
      public:
        ConstUInt(unsigned int value);
    };

    class ConstFloat: public Const {
      private:
        float value;
      public:
        ConstFloat(float value);
    };

}


#endif //HALIDE_CONST_H
