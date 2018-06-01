%module SatHelper
%{
#include "SatHelper/sathelper.h"
%}


%rename(concat) operator<<;

%include "std_string.i"
%include "std_vector.i"
%include "std_list.i"
%include "std_deque.i"
%include "std_map.i"

%include "../../includes/SatHelper/sathelper.h"
%include "../../includes/SatHelper/configparser.h"
%include "../../includes/SatHelper/correlator.h"
%include "../../includes/SatHelper/viterbi27.h"
%include "../../includes/SatHelper/reedsolomon.h"
%include "../../includes/SatHelper/packetfixer.h"
%include "../../includes/SatHelper/screenmanager.h"
%include "../../includes/SatHelper/ipaddress.h"
%include "../../includes/SatHelper/socket.h"
%include "../../includes/SatHelper/tcpsocket.h"
%include "../../includes/SatHelper/tcpserver.h"
%include "../../includes/SatHelper/tcpclient.h"
%include "../../includes/SatHelper/udpsocket.h"
%include "../../includes/SatHelper/derandomizer.h"
%include "../../includes/SatHelper/tools.h"
%include "../../includes/SatHelper/differentialencoding.h"
%include "../../includes/SatHelper/circularbuffer.h"

%include "../../includes/SatHelper/exceptions.h"

%include "../../includes/SatHelper/dsp/agc.h"
%include "../../includes/SatHelper/dsp/clockrecovery.h"
%include "../../includes/SatHelper/dsp/controlloop.h"
%include "../../includes/SatHelper/dsp/costasloop.h"
%include "../../includes/SatHelper/dsp/fftwindows.h"
%include "../../includes/SatHelper/dsp/filters.h"
%include "../../includes/SatHelper/dsp/firfilter.h"
%include "../../includes/SatHelper/dsp/firinterpolator.h"
%include "../../includes/SatHelper/dsp/firkernel.h"
%include "../../includes/SatHelper/info.h"
%include "../../includes/SatHelper/extensions.h"

%extend SatHelper::ConfigParser {
    SatHelper::ConfigParser __getitem__(const std::string &key) {
        return (*($self))[key];
    }
}