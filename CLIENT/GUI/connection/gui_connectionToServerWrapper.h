#ifndef GUI_CONNECTIONTOSERVERWRAPPER_H
#define GUI_CONNECTIONTOSERVERWRAPPER_H

#include "../../connection_to_server.h"

class GIMPdocs;

class GUI_ConnectionToServerWrapper
{
public:
    static int requestTryLoginWrapper(GIMPdocs *gimpdocs, QString username, QString password);


};

#endif // GUI_CONNECTIONTOSERVERWRAPPER_H
