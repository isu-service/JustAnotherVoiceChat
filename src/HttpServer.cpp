/*
 * File: HttpServer.cpp
 * Date: 09.02.2018
 *
 * MIT License
 *
 * Copyright (c) 2018 AlternateVoice
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "HttpServer.h"

#include <iostream>
#include <string.h>

HttpServer::HttpServer() {
  _daemon = nullptr;
}

HttpServer::~HttpServer() {
  close();
}

bool HttpServer::open(uint16_t port) {
  close();

  _daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, port, NULL, NULL, &HttpServer::requestHandler, NULL, MHD_OPTION_END);
  if (_daemon == NULL) {
    _daemon = nullptr;
    return false;
  }

  return true;
}

void HttpServer::close() {
  if (_daemon == nullptr) {
    return;
  }

  MHD_stop_daemon(_daemon);
  _daemon = nullptr;
}

bool HttpServer::isOpen() const {
  return _daemon != nullptr;
}

int HttpServer::handleRequest(struct MHD_Connection *connection, const char *url, const char *method, const char *uploadData, size_t *uploadDataSize) {
  std::cout << method << " " << url << std::endl;

  const char *page = "<html><body>Hello World!</body></html>";

  struct MHD_Response *response;
  int ret;

  response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);

  ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);

  return ret;
}

int HttpServer::requestHandler(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *uploadData, size_t *uploadDataSize, void **ptr) {
  auto server = (HttpServer *)cls;
  return server->handleRequest(connection, url, method, uploadData, uploadDataSize);
}