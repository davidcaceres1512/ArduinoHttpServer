//
//! \file
//  ArduinoHttpServer
//
//  Created by Sander van Woensel on 23-01-16.
//  Copyright (c) 2016 Sander van Woensel. All rights reserved.
//
//! The URL/path provided after the HTTP method.

#include "HttpResource.hpp"

#include <WString.h>

ArduinoHttpServer::HttpResource::HttpResource(const String& resource) :
   m_resource(resource)
{
}

ArduinoHttpServer::HttpResource::HttpResource() :
   m_resource()
{
}

// TODO: default?
ArduinoHttpServer::HttpResource& ArduinoHttpServer::HttpResource::operator=(const ArduinoHttpServer::HttpResource& other)
{
   m_resource = other.m_resource;

   return *this;
}


bool ArduinoHttpServer::HttpResource::isValid()
{
   return m_resource.length() > 0;
}

//! Retrieve resource part at the specified index.
//! \details E.g. HttpResource("/api/sensors/1/state")[1]
//!    returns "sensors".
//! \returns Empty string when index specified is out of range. 
String ArduinoHttpServer::HttpResource::operator[](const unsigned int index) const
{
   int fromOffset(0);

   // Forward till we reach desired index.
   for (unsigned int currentIndex=0; currentIndex <= index; ++currentIndex)
   {
      fromOffset = m_resource.indexOf(RESOURCE_SEPERATOR, fromOffset);
      if(fromOffset == -1)
      {
         return String("");
      }

      ++fromOffset; // Seek past '/'.
   }

   // Find next possible '/' or end.
   int toOffset( m_resource.indexOf(RESOURCE_SEPERATOR, fromOffset) );
   if(toOffset == -1)
   {
      toOffset = m_resource.length();
   }

   return m_resource.substring(fromOffset, toOffset);

}


const String& ArduinoHttpServer::HttpResource::toString() const
{
   return m_resource;
}
