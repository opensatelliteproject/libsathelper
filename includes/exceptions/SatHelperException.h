/*
 * SatHelperException.h
 *
 *  Created on: 04/11/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_EXCEPTIONS_SATHELPEREXCEPTION_H_
#define INCLUDES_EXCEPTIONS_SATHELPEREXCEPTION_H_

#include <exception>
#include <string>

class SatHelperException: public std::exception {
public:

	SatHelperException(): msg_("") {}

	SatHelperException(const char *message): msg_(message) {}

	SatHelperException(const std::string &message): msg_(message) {}

    virtual ~SatHelperException() throw (){}

    virtual const char* what() const throw () { return msg_.c_str(); }

    virtual const std::string message() { return msg_; }

protected:
    /** Error message.
     */
    std::string msg_;
};


#endif /* INCLUDES_EXCEPTIONS_SATHELPEREXCEPTION_H_ */
