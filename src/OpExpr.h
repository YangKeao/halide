//
// Created by yangkeao on 6/13/19.
//

#ifndef HALIDE_OPEXPR_H
#define HALIDE_OPEXPR_H


#include "Const.h"

namespace Halide {
    enum Op {
        Add,
        Minus,
        Mul,
        Div,
    };

    template<Op op>
    class OpExpr: public Expr {
      private:
        Expr* lhs;
        Expr* rhs;
        Op _op = op;
      public:
        Op getOp() const {
            return _op;
        }

        template<typename T>
        OpExpr(Expr &lhs, T& rhs): lhs((Expr*)&lhs), rhs((Expr*)new Const(rhs)) {}

        void *codegen(CompileCtx&) override;
    };

    template<Op op>
    void *OpExpr<op>::codegen(CompileCtx& ctx) {
        auto *left = (llvm::Value*)lhs->codegen(ctx);
        auto *right = (llvm::Value*)rhs->codegen(ctx);

        switch (_op) {
            case Op::Add: {
                return ctx.llvm_builder.CreateAdd(left, right, "add_tmp");
            }
            case Op::Minus: {
                return ctx.llvm_builder.CreateSub(left, right, "sub_tmp");
            }
            case Op::Mul: {
                return ctx.llvm_builder.CreateMul(left, right, "mul_tmp");
            }
            case Op::Div: {
                return ctx.llvm_builder.CreateSDiv(left, right, "div_tmp");
            }
        }
    }


    template<typename T>
    Expr& operator+(Expr& lhs, T rhs) {
        return *new OpExpr<Op::Add>(lhs, rhs);
    }

    template<typename T>
    Expr& operator-(Expr& lhs, T rhs) {
        return *new OpExpr<Op::Minus>(lhs, rhs);
    }

    template<typename T>
    Expr& operator*(Expr& lhs, T rhs) {
        return *new OpExpr<Op::Mul>(lhs, rhs);
    }

    template<typename T>
    Expr& operator/(Expr& lhs, T rhs) {
        return *new OpExpr<Op::Div>(lhs, rhs);
    }
}


#endif //HALIDE_OPEXPR_H
