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

#include "JDWPClient.h"

#include <QtCore/QDebug>

#include "JDWPProtocol.h"
#include "JDWPReply.h"
#include "JDWPCommand.h"

JDWPClient::JDWPClient()
{
	tcpSocket_ = new QTcpSocket();
	QObject::connect(tcpSocket_, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error),
						  &JDWPClient::handleSocketError);
	QObject::connect(tcpSocket_, &QTcpSocket::readyRead, this, &JDWPClient::read);
	QObject::connect(tcpSocket_, &QTcpSocket::connected, [this]() {connected_ = true;});
	tcpSocket_->connectToHost(remoteHost_, remotePort_);
}

JDWPClient::~JDWPClient()
{
	tcpSocket_->abort();
	delete tcpSocket_;
}

void JDWPClient::handleSocketError(QAbstractSocket::SocketError socketError)
{
	qWarning() << "#ERROR" << socketError;
}

void JDWPClient::read()
{
	QByteArray data = tcpSocket_->readAll();
	if (data.startsWith("JDWP"))
	{
		ready_ = true;
		return onReady();
	}
	else
	{
		auto reply = JDWPReply::fromPacket(data);
		qDebug() << "Reply error" << reply.error();
		if (reply.error() <= 512) // FIXME remove hardcoded val
		{
			if (auto fun = handlingMap_[reply.id()])
				fun(*this, reply.data());
			else
				;// TODO that is most probably an event
		}
	}
}

void JDWPClient::sendHanshake()
{
	tcpSocket_->write(JDWPProtocol::handshake.toLatin1());
}

void JDWPClient::onReady()
{
	auto command = JDWPCommand(JDWPProtocol::CommandSet::VirtualMachine, 1, nullptr, 0);
	handlingMap_[0] = &JDWPClient::handleVersion;
	tcpSocket_->write(command.packet());
}

QDataStream& operator>>(QDataStream& stream, QString& read)
{
	// String in JDWP are encoded like this: | length | String (without \0) |
	qint32 len;
	stream >> len;
	char data[len + 1];
	stream.readRawData(data, len);
	data[len] = '\0';
	read = QString(data);
	return stream;
}

void JDWPClient::handleVersion(const QByteArray& data)
{
	qint32 jdwpMajor, jdwpMinor;
	QString description, vmVersion, vmName;
	QDataStream dataStream(data);
	dataStream >> description >> jdwpMajor >> jdwpMinor >> vmVersion >> vmName;
	qDebug() << "Version info: \n" << description << jdwpMajor << jdwpMinor << "\n" << vmVersion << vmName;
}
