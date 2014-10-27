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

#include "JDWPCommand.h"

#include <QtCore/QByteArray>
#include <QtCore/QDataStream>

#include <QtCore/QDebug>

int JDWPCommand::packetCounter_ = 0;

JDWPCommand::JDWPCommand(const JDWPProtocol::CommandSet& commandSet, qint8 command, const char* data, int dataSize)
	: commandSet_{static_cast<char>(commandSet)}, command_{command}, data_{data}
{
	id_ = packetCounter_++;
	length_ += dataSize;
}

QByteArray JDWPCommand::packet() const
{
	QByteArray packet;
	QDataStream packetStream(&packet, QIODevice::ReadWrite);
	if (data_)
		packetStream << length_ << id_ << flags_ << commandSet_ << command_ << data_;
	else
		packetStream << length_ << id_ << flags_ << commandSet_ << command_;
	qDebug() << "PACKET" << length_ << id_ << static_cast<int>(flags_) << static_cast<int>(commandSet_) << static_cast<int>(command_);
	return packet;
}



