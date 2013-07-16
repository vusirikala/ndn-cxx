/**
 * @author: Jeff Thompson
 * See COPYING for copyright and distribution information.
 */

#ifndef NDN_NDN_HPP
#define	NDN_NDN_HPP

#include "Closure.hpp"
#include "Interest.hpp"
#include "transport/Transport.hpp"
#include "encoding/BinaryXMLElementReader.hpp"

using namespace std;

namespace ndn {

class NDN : public ElementListener {
public:
  NDN(const ptr_lib::shared_ptr<Transport> &transport, const char *host, unsigned short port, const ptr_lib::shared_ptr<Closure> &tempClosure)
  : transport_(transport), host_(host), port_(port), tempClosure_(tempClosure) 
  {
  }
  
  /**
   * Encode name as an Interest. If interestTemplate is not 0, use its interest selectors.
   * Send the interest through the transport, read the entire response and call
   * closure->upcall(UPCALL_CONTENT (or UPCALL_CONTENT_UNVERIFIED),
   *                 UpcallInfo(this, interest, 0, contentObject)).
   * @param name reference to a Name for the interest.  This does not keep a pointer to the Name object.
   * @param closure a shared_ptr for the Closure.  This uses shared_ptr to take another reference to the object.
   * @param interestTemplate if not 0, copy interest selectors from the template.   This does not keep a pointer to the Interest object.
   */
  void expressInterest(const Name &name, const ptr_lib::shared_ptr<Closure> &closure, const Interest *interestTemplate);
  
  Transport &tempGetTransport() { return *transport_; }
  
  virtual void onReceivedElement(unsigned char *element, unsigned int elementLength);
  
private:
  ptr_lib::shared_ptr<Transport> transport_;
  string host_;
  unsigned short port_;
  ptr_lib::shared_ptr<Closure> tempClosure_;
};

}

#endif