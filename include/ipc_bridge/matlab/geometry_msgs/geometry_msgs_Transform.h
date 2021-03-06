/*
ipc_bridge: ROS-MATLAB interface via CMU's IPC
Copyright (C) 2014  Nathan Michael

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#ifndef IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_TRANSFORM
#define IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_TRANSFORM
#include <ipc_bridge/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/geometry_msgs_Transform.h>

#include <ipc_bridge/matlab/geometry_msgs/geometry_msgs_Vector3.h>
#include <ipc_bridge/matlab/geometry_msgs/geometry_msgs_Quaternion.h>

namespace ipc_bridge_matlab
{
  namespace geometry_msgs
  {
    namespace Transform
    {
      static mxArray* ProcessMessage(const ipc_bridge::geometry_msgs::Transform &msg)
      {
        const char *fields[] = {"translation", "rotation"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        mxSetField(out, 0, "translation",
                   ipc_bridge_matlab::geometry_msgs::Vector3::ProcessMessage(msg.translation));
        mxSetField(out, 0, "rotation",
                   ipc_bridge_matlab::geometry_msgs::Quaternion::ProcessMessage(msg.rotation));

        return out;
      }

      static int ProcessArray(const mxArray *a,
                              ipc_bridge::geometry_msgs::Transform &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "translation");
        ipc_bridge_matlab::geometry_msgs::Vector3::ProcessArray(field, msg.translation);

        field = mxGetField(a, 0, "rotation");
        ipc_bridge_matlab::geometry_msgs::Quaternion::ProcessArray(field, msg.rotation);

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::geometry_msgs::Transform &msg)
      {
        ipc_bridge_matlab::geometry_msgs::Vector3::Cleanup(msg.translation);
        ipc_bridge_matlab::geometry_msgs::Quaternion::Cleanup(msg.rotation);
      }
    }
  }
}
#endif
