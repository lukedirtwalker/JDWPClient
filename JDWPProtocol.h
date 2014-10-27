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
		enum class CommandSet : qint8 {VirtualMachine = 1, ReferenceType = 2, ClassType = 3, ArrayType = 4,
											  InterfaceType = 5, Method = 6, Field = 8, ObjectReference = 9, StringReference = 10,
											  ThreadReference = 11, ThreadGroupReference = 12, ArrayReference = 13,
											  ClassLoaderReference = 14, EventRequest = 15, StackFrame = 16,
											  ClassObjectReference = 17, Event = 64};

		// Following values can be generated with regex:
		// Copy the sublist of a command set from:
		// http://docs.oracle.com/javase/7/docs/platform/jpda/jdwp/jdwp-protocol.html
		// to a text editor (e.g. Kate) search for "(^[^ ]+) \(([0-9]+)\)\n" and replace with "\1 = \2, "
		// minimal manual interaction might be needed
		enum class VirtualMachineCommands : qint8 {Version = 1, ClassesBySignature = 2, AllClasses = 3, AllThreads = 4,
																 TopLevelThreadGroups = 5, Dispose = 6, IDSizes = 7, Suspend = 8,
																 Resume = 9, Exit = 10, CreateString = 11, Capabilities = 12,
																 ClassPaths = 13, DisposeObjects = 14, HoldEvents = 15,
																 ReleaseEvents = 16, CapabilitiesNew = 17, RedefineClasses = 18,
																 SetDefaultStratum = 19, AllClassesWithGeneric = 20, InstanceCounts = 21
																};
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


		// Following values can be generated with regex:
		// Copy the table (e.g. http://docs.oracle.com/javase/7/docs/platform/jpda/jdwp/jdwp-protocol.html#JDWP_EventKind)
		// to a text editor (e.g. Kate) search for "(^[^\t]+)\t([^\t]+)[^\n]+\n" and replace with: "\1 = \2, "
		// minimal manual interaction might be needed
		enum class EventKind : qint8 {SINGLE_STEP = 1, BREAKPOINT = 2, FRAME_POP = 3, EXCEPTION = 4, USER_DEFINED = 5,
												THREAD_START = 6, THREAD_DEATH = 7, THREAD_END = 7, CLASS_PREPARE = 8,
												CLASS_UNLOAD = 9, CLASS_LOAD = 10, FIELD_ACCESS = 20, FIELD_MODIFICATION = 21,
												EXCEPTION_CATCH = 30, METHOD_ENTRY = 40, METHOD_EXIT = 41,
												METHOD_EXIT_WITH_RETURN_VALUE = 42, MONITOR_CONTENDED_ENTER = 43,
												MONITOR_CONTENDED_ENTERED = 44, MONITOR_WAIT = 45, MONITOR_WAITED = 46,
												VM_START = 90, VM_INIT = 90, VM_DEATH = 99, VM_DISCONNECTED = 100};

		enum class ThreadStatus : qint32 {ZOMBIE = 0, RUNNING = 1, SLEEPING = 2, MONITOR = 3, WAIT = 4};

		enum class Error : qint16 {NONE = 0, INVALID_THREAD = 10, INVALID_THREAD_GROUP = 11, INVALID_PRIORITY = 12,
											THREAD_NOT_SUSPENDED = 13, THREAD_SUSPENDED = 14, THREAD_NOT_ALIVE = 15,
											INVALID_OBJECT = 20, INVALID_CLASS = 21, CLASS_NOT_PREPARED = 22,
											INVALID_METHODID = 23, INVALID_LOCATION = 24, INVALID_FIELDID = 25,
											INVALID_FRAMEID = 30, NO_MORE_FRAMES = 31, OPAQUE_FRAME = 32, NOT_CURRENT_FRAME = 33,
											TYPE_MISMATCH = 34, INVALID_SLOT = 35, DUPLICATE = 40, NOT_FOUND = 41,
											INVALID_MONITOR = 50, NOT_MONITOR_OWNER = 51, INTERRUPT = 52,
											INVALID_CLASS_FORMAT = 60, CIRCULAR_CLASS_DEFINITION = 61, FAILS_VERIFICATION = 62,
											ADD_METHOD_NOT_IMPLEMENTED = 63, SCHEMA_CHANGE_NOT_IMPLEMENTED = 64,
											INVALID_TYPESTATE = 65, HIERARCHY_CHANGE_NOT_IMPLEMENTED = 66,
											DELETE_METHOD_NOT_IMPLEMENTED = 67, UNSUPPORTED_VERSION = 68, NAMES_DONT_MATCH = 69,
											CLASS_MODIFIERS_CHANGE_NOT_IMPLEMENTED = 70,
											METHOD_MODIFIERS_CHANGE_NOT_IMPLEMENTED = 71, NOT_IMPLEMENTED = 99, NULL_POINTER = 100,
											ABSENT_INFORMATION = 101, INVALID_EVENT_TYPE = 102, ILLEGAL_ARGUMENT = 103,
											OUT_OF_MEMORY = 110, ACCESS_DENIED = 111, VM_DEAD = 112, INTERNAL = 113,
											UNATTACHED_THREAD = 115, INVALID_TAG = 500, ALREADY_INVOKING = 502,
											INVALID_INDEX = 503, INVALID_LENGTH = 504, INVALID_STRING = 506,
											INVALID_CLASS_LOADER = 507, INVALID_ARRAY = 508, TRANSPORT_LOAD = 509,
											TRANSPORT_INIT = 510, NATIVE_METHOD = 511, INVALID_COUNT = 512};

		enum class SuspendPolicy : qint8 {NONE = 0, EVENT_THREAD = 1, ALL = 2};

		enum class TypeTagKind : qint8 {CLASS = 1, INTERFACE = 2, ARRAY = 3};

		enum class ClassStatus : qint32 {VERIFIED = 1, PREPARED = 2, INITIALIZED = 4, ERROR = 8};
};
