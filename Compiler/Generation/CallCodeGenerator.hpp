//
//  CallCodeGenerator.hpp
//  Emojicode
//
//  Created by Theo Weidmann on 05/08/2017.
//  Copyright © 2017 Theo Weidmann. All rights reserved.
//

#ifndef CallCodeGenerator_hpp
#define CallCodeGenerator_hpp

#include "Functions/CallType.h"
#include <string>
#include <vector>

namespace llvm {
class Value;
}  // namespace llvm

namespace EmojicodeCompiler {

class FunctionCodeGenerator;
class Type;
class Function;
class ASTArguments;

class CallCodeGenerator {
public:
    CallCodeGenerator(FunctionCodeGenerator *fg, CallType callType) : fg_(fg), callType_(callType) {}
    llvm::Value* generate(llvm::Value *callee, const Type &calleeType, const ASTArguments &args,
                          const std::u32string &name);
protected:
    virtual Function* lookupFunction(const Type &type, const std::u32string &name);
    virtual llvm::Value* createCall(const std::vector<llvm::Value *> &args, const Type &type,
                                    const std::u32string &name);
    FunctionCodeGenerator* fg() const { return fg_; }
private:
    llvm::Value* createDynamicDispatch(Function *function, const std::vector<llvm::Value *> &args);
    llvm::Value* createDynamicProtocolDispatch(Function *function, std::vector<llvm::Value *> args,
                                               const Type &calleeType);
    llvm::Value* dispatchFromVirtualTable(Function *function, llvm::Value *virtualTable,
                                          const std::vector<llvm::Value *> &args);
    FunctionCodeGenerator *fg_;
    CallType callType_;
};

class TypeMethodCallCodeGenerator : public CallCodeGenerator {
    using CallCodeGenerator::CallCodeGenerator;
protected:
    Function* lookupFunction(const Type &type, const std::u32string &name) override;
};

class InitializationCallCodeGenerator : public CallCodeGenerator {
    using CallCodeGenerator::CallCodeGenerator;
protected:
    Function* lookupFunction(const Type &type, const std::u32string &name) override;
};

}  // namespace EmojicodeCompiler

#endif /* CallCodeGenerator_hpp */
