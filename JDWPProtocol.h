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

#include <QtCore/QString>

class JDWPProtocol
{
	public:
		static const QString handshake;

		// http://docs.oracle.com/javase/7/docs/technotes/guides/jpda/jdwp-spec.html
		// http://docs.oracle.com/javase/7/docs/platform/jpda/jdwp/jdwp-protocol.html
		enum class CommandSet : int {VirtualMachine = 1, ReferenceType = 2, ClassType = 3, ArrayType = 4,
											  InterfaceType = 5, Method = 6, Field = 8, ObjectReference = 9, StringReference = 10,
											  ThreadReference = 11, ThreadGroupReference = 12, ArrayReference = 13,
											  ClassLoaderReference = 14, EventRequest = 15, StackFrame = 16,
											  ClassObjectReference = 17, Event = 64};

		enum class VirtualMachineCommands : int {};
		enum class ReferenceTypeCommands : int {};
		enum class ClassTypeCommands : int {};
		enum class ArrayTypeCommands : int {};
		enum class InterfaceTypeCommands : int {};
		enum class MethodCommands : int {};
		enum class FieldCommands : int {};
		enum class ObjectReferenceCommands : int {};
		enum class StringReferenceCommands : int {};
		enum class ThreadReferenceCommands : int {};
		enum class ThreadGroupReferenceCommands : int {};
		enum class ArrayReferenceCommands : int {};
		enum class ClassLoaderReferenceCommands : int {};
		enum class EventRequestCommands : int {};
		enum class StackFrameCommands : int {};
		enum class ClassObjectReferenceCommands : int {};
		enum class EventCommands : int {};
};
