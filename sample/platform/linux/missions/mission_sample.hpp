/*! @file mission_sample.hpp
 *  @version 4.0.0
 *  @date Jun 05 2017
 *
 *  @brief
 *  GPS Missions API usage in a Linux environment.
 *  Shows example usage of the Waypoint Missions and Hotpoint Missions through
 * the
 *  Mission Manager API.
 *
 *  @Copyright (c) 2017 DJI
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef DJIOSDK_MISSIONSAMPLE_HPP
#define DJIOSDK_MISSIONSAMPLE_HPP

// System Includes
#include <cmath>
#include <vector>

// DJI OSDK includes
#include <dji_vehicle.hpp>

// Helpers
#include <dji_linux_helpers.hpp>
#include "csv_reader.hpp"
void setWaypointFromCSVRow(WayPointInitSettings* fdata,std::string&& filename, unsigned rowNum);

// Subscription not supported in Matrice 100
bool setUpSubscription(DJI::OSDK::Vehicle* vehicle, int responseTimeout);
bool teardownSubscription(DJI::OSDK::Vehicle* vehicle, const int pkgIndex,
                          int responseTimeout);

bool runWaypointMission(DJI::OSDK::Vehicle* vehicle, uint8_t numWaypoints,
                        int responseTimeout);

void setWaypointDefaults(DJI::OSDK::WayPointSettings* wp);
void setWaypointInitDefaults(DJI::OSDK::WayPointInitSettings* fdata);

std::vector<DJI::OSDK::WayPointSettings> createWaypoints(
  DJI::OSDK::Vehicle* vehicle, int numWaypoints,
  DJI::OSDK::float64_t distanceIncrement, DJI::OSDK::float32_t start_alt);

std::vector<DJI::OSDK::WayPointSettings> generateWaypointsPolygon(
  DJI::OSDK::WayPointSettings* start_data, DJI::OSDK::float64_t increment,
  int num_wp);

void uploadWaypoints(DJI::OSDK::Vehicle*                       vehicle,
                     std::vector<DJI::OSDK::WayPointSettings>& wp_list,
                     int                                       responseTimeout);

bool runHotpointMission(DJI::OSDK::Vehicle* vehicle, int initialRadius,
                        int responseTimeout);

const int DEFAULT_PACKAGE_INDEX = 0;

#endif // DJIOSDK_MISSIONSAMPLE_HPP