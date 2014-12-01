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

#pragma once

#include <functional>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QHash>

#include "JDWPProtocol.h"

class JDWPCommand;

struct JDWPClass
{
		JDWPClass() {}
		JDWPClass(JDWPProtocol::TypeTagKind kind, qint64 typeId, QString signature, JDWPProtocol::ClassStatus status)
			: kind_{kind}, typeId_{typeId}, signature_{signature}, status_{status} {}
		JDWPProtocol::TypeTagKind kind_{};
		qint64 typeId_{};
		QString signature_;
		JDWPProtocol::ClassStatus status_{};
};

class JDWPClient : public QObject
{
	Q_OBJECT

	public:
		JDWPClient(QString remoteHost="localhost", int remotePort=8000);
		~JDWPClient();

		static void handleSocketError(QAbstractSocket::SocketError socketError);
		void read();

		void sendHanshake();

		void onReady();

		void sendCommand(const JDWPCommand& command, std::function<void(JDWPClient&, const QByteArray&)> replyHandler);

		void handleVersion(const QByteArray& data);

		void handleAllClasses(const QByteArray& data);

	private:
		QHash<int, std::function<void(JDWPClient&, const QByteArray&)>> handlingMap_;
		QHash<QString, JDWPClass> classMap_;
		QString remoteHost_;
		int remotePort_;
		QTcpSocket* tcpSocket_{};
		bool connected_{};
		bool ready_{};
};
