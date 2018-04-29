//
// Created by vrudenko on 29/04/18.
//

#ifndef SNTKURSACH_EXCEPTIONS_H
#define SNTKURSACH_EXCEPTIONS_H

class Exceptions {
    public:
        static std::string error(int error);
        enum err {FEW_POINTS, FILE_ERROR};
};


#endif //SNTKURSACH_EXCEPTIONS_H
