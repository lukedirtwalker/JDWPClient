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

#include "JDWPReply.h"

#include <iostream>

#include <QtCore/QDataStream>
#include <QtCore/QIODevice>

#include <QtCore/QDebug>

JDWPReply JDWPReply::fromPacket(QByteArray& packet)
{
	qint32 length, id;
	qint8 flags;
	qint16 error;
	QDataStream packetStream(packet);
	packetStream >> length >> id >> flags >> error;
	int dataSize = length - headerSize_;
	qDebug() << "Received data size" <<dataSize;
	if (dataSize > 0)
	{
		qDebug() << "DEV POS: " << packetStream.device()->pos();
		auto byteArray = packetStream.device()->readAll();

		QDataStream replyStream(byteArray);
		char* description;
		int major, minor;
		replyStream >> description >> major >> minor;
		qDebug() << "Version" << major << minor;

		return JDWPReply(length, id, flags, error, byteArray);
	}
	else
	{
		return JDWPReply(length, id, flags, error, QByteArray());
	}
}

JDWPReply::JDWPReply(int length, int id, char flags, short errorCode, QByteArray data)
	: length_{length}, id_{id}, flags_{flags}, errorCode_{errorCode}, data_{data}
{
	qDebug() << "PACKET REPLY" << length_ << id_ << static_cast<int>(flags_) << static_cast<int>(errorCode_) << data_;
}
