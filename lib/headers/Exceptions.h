#ifndef SNTKURSACH_EXCEPTIONS_H
#define SNTKURSACH_EXCEPTIONS_H

/** Class to represent exceptions.
 *
 * @bug Rewrite for standards
 */
class Exceptions {
    public:
        static std::string error(int error);
        enum err {FEW_POINTS, FILE_ERROR};
};


#endif //SNTKURSACH_EXCEPTIONS_H
