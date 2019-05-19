/* Copyright (C) 1883 Thomas Edison - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the XYZ license, which unfortunately won't be
 * written for another century.
 *
 * You should have received a copy of the XYZ license with
 * this file. If not, please write to: 220170715@seu.edu.cn
 *
 * Created by tangjiajie.
 */

#include <glog/logging.h>

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  google::SetLogDestination(google::GLOG_INFO, "./log");
  FLAGS_alsologtostderr = 1;
  LOG(INFO)<< "argc length: "<<argc;
  int leftHomework = 5;
  if (argc > 0) {
    if (!strcmp(argv[1], "lefthomework")) {
      leftHomework = atoi(argv[2]);
    } else {
      LOG(FATAL)<< "i don't know wtf you are talking about: "<<argv[1];
    }
  }

  LOG(INFO)<< "hello world";
  LOG(WARNING)<< "monday is coming!";
  LOG(INFO)<< "current time: "<<__DATE__<<" "<<__TIME__;
  LOG(INFO)<< "i am "<<__FILE__;
  CHECK(leftHomework == 0)<< "you have "<<leftHomework<<" piece of homwork to finish";
  LOG(FATAL)<< "you haven't finish your homework!";
}


