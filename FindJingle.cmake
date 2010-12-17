FIND_PATH(JINGLE_INCLUDE_DIR talk/base/openssladapter.h ${CMAKE_CURRENT_SOURCE_DIR}/libjingle/ /usr/include/ /usr/local/include/)

FIND_LIBRARY(JINGLE_LIBRARY NAMES libjingle.a PATH /usr/lib /usr/local/lib)

MESSAGE(STATUS ${JINGLE_LIBRARY})

IF (JINGLE_INCLUDE_DIR AND JINGLE_LIBRARY)
   SET(JINGLE_FOUND TRUE)
ENDIF (JINGLE_INCLUDE_DIR AND JINGLE_LIBRARY)

IF (JINGLE_FOUND)
  MESSAGE(STATUS "Found Jingle: ${JINGLE_LIBRARY}")
ELSE (JINGLE_FOUND)
  MESSAGE(FATAL_ERROR "Could not find Jingle")
ENDIF (JINGLE_FOUND)



FIND_LIBRARY(EXPAT_LIBRARY NAMES libexpat.a PATH /usr/lib /usr/local/lib)

IF (EXPAT_LIBRARY)
  SET(EXPAT_FOUND TRUE)
ENDIF (EXPAT_LIBRARY)

IF (EXPAT_FOUND)
   IF (NOT Expat_FIND_QUIETLY)
      MESSAGE(STATUS "Found Expat: ${EXPAT_LIBRARY}")
   ENDIF (NOT Expat_FIND_QUIETLY)
ELSE (EXPAT_FOUND)
  MESSAGE(FATAL_ERROR "Could not find Expat")
ENDIF (EXPAT_FOUND)



FIND_LIBRARY(XMPP_LIBRARY NAMES libxmpphelp.a PATH /usr/lib /usr/local/lib ${CMAKE_CURRENT_SOURCE_DIR}/libjingle/talk/build/dbg/lib)

IF (XMPP_LIBRARY)
   SET(XMPP_FOUND TRUE)
ENDIF (XMPP_LIBRARY)

IF (XMPP_FOUND)
   IF (NOT Xmpp_FIND_QUIETLY)
      MESSAGE(STATUS "Found Xmpp: ${XMPP_LIBRARY}")
   ENDIF (NOT Xmpp_FIND_QUIETLY)
ELSE (XMPP_FOUND)
  MESSAGE(FATAL_ERROR "Could not find Xmpp")
ENDIF (XMPP_FOUND)



FIND_LIBRARY(SRTP_LIBRARY NAMES srtp PATH /usr/lib /usr/local/lib ${CMAKE_CURRENT_SOURCE_DIR}/libjingle/talk/build/dbg/lib)

IF (SRTP_LIBRARY)
   SET(SRTP_FOUND TRUE)
ENDIF (SRTP_LIBRARY)

IF (SRTP_FOUND)
   IF (NOT Srtp_FIND_QUIETLY)
      MESSAGE(STATUS "Found Srtp: ${SRTP_LIBRARY}")
   ENDIF (NOT Srtp_FIND_QUIETLY)
ELSE (SRTP_FOUND)
  MESSAGE(FATAL_ERROR "Could not find Srtp")
ENDIF (SRTP_FOUND)

set(JINGLE_LIBRARIES ${JINGLE_LIBRARY} ${EXPAT_LIBRARY} ${SRTP_LIBRARY} ${XMPP_LIBRARY})