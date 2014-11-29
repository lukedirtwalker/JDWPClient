/***********************************************************************************************************************
**
** Copyright (c) 2011, 2014 ETH Zurich
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
** following conditions are met:
**
**    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following
**      disclaimer.
**    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
**      following disclaimer in the documentation and/or other materials provided with the distribution.
**    * Neither the name of the ETH Zurich nor the names of its contributors may be used to endorse or promote products
**      derived from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
** INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
** SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
***********************************************************************************************************************/

#include <QCoreApplication>
#include <QCommandLineParser>

#include "JDWPClient.h"

int main(int argc, char *argv[])
{
   QCoreApplication app(argc, argv);
   QCoreApplication::setApplicationName("jdwpclient");
   QCoreApplication::setApplicationVersion("1.0");

   QCommandLineParser parser;
   parser.setApplicationDescription("client for Java Device Wire Protocol");
   parser.addHelpOption();
   parser.addVersionOption();

   QCommandLineOption hostOption("host",
   QCoreApplication::translate("main", "host to connect."),
   QCoreApplication::translate("main", "host"));
   hostOption.setDefaultValue("localhost");
   parser.addOption(hostOption);

   QCommandLineOption portOption(QStringList() << "p" << "port",
   QCoreApplication::translate("main", "port to connect."),
   QCoreApplication::translate("main", "port"));
   portOption.setDefaultValue("8000");
      
   parser.addOption(portOption);

   parser.process(app);

	JDWPClient client(parser.value(hostOption), parser.value(portOption).toInt());
	client.sendHanshake();

	return app.exec();
}
