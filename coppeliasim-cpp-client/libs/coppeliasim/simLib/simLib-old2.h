typedef int (__cdecl *ptrSimGetMaterialId)(const char* materialName);
typedef int (__cdecl *ptrSimGetShapeMaterial)(int shapeHandle);
typedef int (__cdecl *ptrSimHandleVarious)();
typedef int (__cdecl *ptrSimSerialPortOpen)(int portNumber,int baudRate,void* reserved1,void* reserved2);
typedef int (__cdecl *ptrSimSerialPortClose)(int portNumber);
typedef int (__cdecl *ptrSimSerialPortSend)(int portNumber,const char* data,int dataLength);
typedef int (__cdecl *ptrSimSerialPortRead)(int portNumber,char* buffer,int dataLengthToRead);
typedef int (__cdecl *ptrSimGetPathPlanningHandle)(const char* pathPlanningObjectName);
typedef int (__cdecl *ptrSimGetMotionPlanningHandle)(const char* motionPlanningObjectName);
typedef int (__cdecl *ptrSimRemoveMotionPlanning)(int motionPlanningHandle);
typedef int (__cdecl *ptrSimPerformPathSearchStep)(int temporaryPathSearchObject,bool abortSearch);
typedef int (__cdecl *ptrSimLockInterface)(bool locked);
typedef int (__cdecl *ptrSimCopyPasteSelectedObjects)();
typedef int (__cdecl *ptrSimResetPath)(int pathHandle);
typedef int (__cdecl *ptrSimResetJoint)(int jointHandle);
typedef int (__cdecl *ptrSimAppendScriptArrayEntry)(const char* reservedSetToNull,int scriptHandleOrType,const char* arrayNameAtScriptName,const char* keyName,const char* data,const int* what);
typedef int (__cdecl *ptrSimClearScriptVariable)(const char* reservedSetToNull,int scriptHandleOrType,const char* variableNameAtScriptName);
typedef int (__cdecl *ptrSimAddSceneCustomData)(int header,const char* data,int dataLength);
typedef int (__cdecl *ptrSimGetSceneCustomDataLength)(int header);
typedef int (__cdecl *ptrSimGetSceneCustomData)(int header,char* data);
typedef int (__cdecl *ptrSimAddObjectCustomData)(int objectHandle,int header,const char* data,int dataLength);
typedef int (__cdecl *ptrSimGetObjectCustomDataLength)(int objectHandle,int header);
typedef int (__cdecl *ptrSimGetObjectCustomData)(int objectHandle,int header,char* data);
typedef int (__cdecl *ptrSimCreateUI)(const char* uiName,int menuAttributes,const int* clientSize,const int* cellSize,int* buttonHandles);
typedef int (__cdecl *ptrSimCreateUIButton)(int uiHandle,const int* position,const int* size,int buttonProperty);
typedef int (__cdecl *ptrSimGetUIHandle)(const char* uiName);
typedef int (__cdecl *ptrSimGetUIProperty)(int uiHandle);
typedef int (__cdecl *ptrSimGetUIEventButton)(int uiHandle,int* auxiliaryValues);
typedef int (__cdecl *ptrSimSetUIProperty)(int uiHandle,int elementProperty);
typedef int (__cdecl *ptrSimGetUIButtonProperty)(int uiHandle,int buttonHandle);
typedef int (__cdecl *ptrSimSetUIButtonProperty)(int uiHandle,int buttonHandle,int buttonProperty);
typedef int (__cdecl *ptrSimGetUIButtonSize)(int uiHandle,int buttonHandle,int* size);
typedef int (__cdecl *ptrSimSetUIButtonLabel)(int uiHandle,int buttonHandle,const char* upStateLabel,const char* downStateLabel);
typedef char* (__cdecl *ptrSimGetUIButtonLabel)(int uiHandle,int buttonHandle);
typedef int (__cdecl *ptrSimSetUISlider)(int uiHandle,int buttonHandle,int position);
typedef int (__cdecl *ptrSimGetUISlider)(int uiHandle,int buttonHandle);
typedef int (__cdecl *ptrSimSetUIButtonTexture)(int uiHandle,int buttonHandle,const int* size,const char* textureData);
typedef int (__cdecl *ptrSimCreateUIButtonArray)(int uiHandle,int buttonHandle);
typedef int (__cdecl *ptrSimDeleteUIButtonArray)(int uiHandle,int buttonHandle);
typedef int (__cdecl *ptrSimRemoveUI)(int uiHandle);
typedef int (__cdecl *ptrSimSetUIPosition)(int uiHandle,const int* position);
typedef int (__cdecl *ptrSimGetUIPosition)(int uiHandle,int* position);
typedef int (__cdecl *ptrSimLoadUI)(const char* filename,int maxCount,int* uiHandles);
typedef int (__cdecl *ptrSimSaveUI)(int count,const int* uiHandles,const char* filename);
typedef int (__cdecl *ptrSimHandleGeneralCallbackScript)(int callbackId,int callbackTag,void* additionalData);
typedef int (__cdecl *ptrSimRegisterCustomLuaFunction)(const char* funcName,const char* callTips,const int* inputArgumentTypes,void(*callBack)(struct SLuaCallBack* p));
typedef int (__cdecl *ptrSimRegisterCustomLuaVariable)(const char* varName,const char* varValue);
typedef int (__cdecl *ptrSimGetMechanismHandle)(const char* mechanismName);
typedef int (__cdecl *ptrSimHandleMechanism)(int mechanismHandle);
typedef int (__cdecl *ptrSimHandleCustomizationScripts)(int callType);
typedef int (__cdecl *ptrSimResetMilling)(int objectHandle);
typedef int (__cdecl *ptrSimResetMill)(int millHandle);
typedef int (__cdecl *ptrSimApplyMilling)(int objectHandle);
typedef bool (__cdecl *ptr_simGetParentFollowsDynamic)(const void* shape);
typedef int (__cdecl *ptrSimGetNameSuffix)(const char* name);
typedef int (__cdecl *ptrSimSetNameSuffix)(int nameSuffixNumber);
typedef int (__cdecl *ptrSimAddStatusbarMessage)(const char* message);
typedef char* (__cdecl *ptrSimGetScriptSimulationParameter)(int scriptHandle,const char* parameterName,int* parameterLength);
typedef int (__cdecl *ptrSimSetScriptSimulationParameter)(int scriptHandle,const char* parameterName,const char* parameterValue,int parameterLength);
typedef char* (__cdecl *ptrSimGetScriptRawBuffer)(int scriptHandle,int bufferHandle);
typedef int (__cdecl *ptrSimSetScriptRawBuffer)(int scriptHandle,const char* buffer,int bufferSize);
typedef int (__cdecl *ptrSimReleaseScriptRawBuffer)(int scriptHandle,int bufferHandle);
typedef int (__cdecl *ptrSimRemoveIkGroup)(int ikGroupHandle);
typedef int (__cdecl *ptrSimExportIk)(const char* pathAndFilename,int reserved1,void* reserved2);
typedef int (__cdecl *ptrSimComputeJacobian)(int ikGroupHandle,int options,void* reserved);
typedef int (__cdecl *ptrSimGetIkGroupHandle)(const char* ikGroupName);
typedef int (__cdecl *ptrSimHandleIkGroup)(int ikGroupHandle);
typedef int (__cdecl *ptrSimSetThreadIsFree)(bool freeMode);
typedef int (__cdecl *ptrSimTubeOpen)(int dataHeader,const char* dataName,int readBufferSize,bool notUsedButKeepFalse);
typedef int (__cdecl *ptrSimTubeClose)(int tubeHandle);
typedef int (__cdecl *ptrSimTubeWrite)(int tubeHandle,const char* data,int dataLength);
typedef char* (__cdecl *ptrSimTubeRead)(int tubeHandle,int* dataLength);
typedef int (__cdecl *ptrSimTubeStatus)(int tubeHandle,int* readPacketsCount,int* writePacketsCount);
typedef char* (__cdecl *ptrSimReceiveData)(int dataHeader,const char* dataName,int antennaHandle,int index,int* dataLength,int* senderID,int* dataHeaderR,char** dataNameR);
typedef int (__cdecl *ptrSimInsertPathCtrlPoints)(int pathHandle,int options,int startIndex,int ptCnt,const void* ptData);
typedef int (__cdecl *ptrSimCutPathCtrlPoints)(int pathHandle,int startIndex,int ptCnt);
typedef int (__cdecl *ptrSimGetThreadId)();
typedef int (__cdecl *ptrSimSwitchThread)();
typedef int (__cdecl *ptrSimLockResources)(int lockType,int reserved);
typedef int (__cdecl *ptrSimUnlockResources)(int lockHandle);
typedef char* (__cdecl *ptrSimGetUserParameter)(int objectHandle,const char* parameterName,int* parameterLength);
typedef int (__cdecl *ptrSimSetUserParameter)(int objectHandle,const char* parameterName,const char* parameterValue,int parameterLength);
typedef int (__cdecl *ptrSimCreateCollection)(const char* collectionName,int options);
typedef int (__cdecl *ptrSimAddObjectToCollection)(int collectionHandle,int objectHandle,int what,int options);
typedef int (__cdecl *ptrSimGetCollectionHandle)(const char* collectionName);
typedef int (__cdecl *ptrSimRemoveCollection)(int collectionHandle);
typedef int (__cdecl *ptrSimEmptyCollection)(int collectionHandle);
typedef char* (__cdecl *ptrSimGetCollectionName)(int collectionHandle);
typedef int (__cdecl *ptrSimSetCollectionName)(int collectionHandle,const char* collectionName);extern ptrSimGetMaterialId simGetMaterialId;
typedef int (__cdecl *ptrSimGetCollisionHandle)(const char* collisionObjectName);
typedef int (__cdecl *ptrSimGetDistanceHandle)(const char* distanceObjectName);
typedef int (__cdecl *ptrSimResetCollision)(int collisionObjectHandle);
typedef int (__cdecl *ptrSimResetDistance)(int distanceObjectHandle);
typedef int (__cdecl *ptrSimHandleCollision)(int collisionObjectHandle);
typedef int (__cdecl *ptrSimReadCollision)(int collisionObjectHandle);
typedef int (__cdecl *ptrSimRemoveBanner)(int bannerID);
typedef char* (__cdecl *ptrSimGetObjectName)(int objectHandle);
typedef int (__cdecl *ptrSimSetObjectName)(int objectHandle,const char* objectName);
typedef char* (__cdecl *ptrSimGetScriptName)(int scriptHandle);
typedef int (__cdecl *ptrSimGetScriptHandle)(const char* scriptName);
typedef int (__cdecl *ptrSimSetScriptVariable)(int scriptHandleOrType,const char* variableNameAtScriptName,int stackHandle);
typedef int (__cdecl *ptrSimGetObjectHandle)(const char* objectAlias);
typedef int (__cdecl *ptrSimGetObjectHandleEx)(const char* objectAlias,int index,int proxy,int options);
typedef int (__cdecl *ptrSimGetScript)(int index);
typedef int (__cdecl *ptrSimGetScriptAssociatedWithObject)(int objectHandle);
typedef int (__cdecl *ptrSimGetCustomizationScriptAssociatedWithObject)(int objectHandle);
typedef int (__cdecl *ptrSimGetObjectAssociatedWithScript)(int scriptHandle);
typedef char* (__cdecl *ptrSimGetObjectConfiguration)(int objectHandle);
typedef int (__cdecl *ptrSimSetObjectConfiguration)(const char* data);
typedef char* (__cdecl *ptrSimGetConfigurationTree)(int objectHandle);
typedef int (__cdecl *ptrSimSetConfigurationTree)(const char* data);
typedef int (__cdecl *ptrSimEnableEventCallback)(int eventCallbackType,const char* plugin,int reserved);
typedef int (__cdecl *ptrSimRMLPosition)(int dofs,double timeStep,int flags,const double* currentPosVelAccel,const double* maxVelAccelJerk,const bool* selection,const double* targetPosVel,double* newPosVelAccel,void* auxData);
typedef int (__cdecl *ptrSimRMLVelocity)(int dofs,double timeStep,int flags,const double* currentPosVelAccel,const double* maxAccelJerk,const bool* selection,const double* targetVel,double* newPosVelAccel,void* auxData);
typedef int (__cdecl *ptrSimRMLPos)(int dofs,double smallestTimeStep,int flags,const double* currentPosVelAccel,const double* maxVelAccelJerk,const bool* selection,const double* targetPosVel,void* auxData);
typedef int (__cdecl *ptrSimRMLVel)(int dofs,double smallestTimeStep,int flags,const double* currentPosVelAccel,const double* maxAccelJerk,const bool* selection,const double* targetVel,void* auxData);
typedef int (__cdecl *ptrSimRMLStep)(int handle,double timeStep,double* newPosVelAccel,void* auxData,void* reserved);
typedef int (__cdecl *ptrSimRMLRemove)(int handle);
typedef int (__cdecl *ptrSimGetSystemTimeInMilliseconds)();
typedef unsigned int (__cdecl *ptrSimGetSystemTimeInMs)(int previousTime);
typedef char* (__cdecl *ptrSimFileDialog)(int mode,const char* title,const char* startPath,const char* initName,const char* extName,const char* ext);
typedef int (__cdecl *ptrSimMsgBox)(int dlgType,int buttons,const char* title,const char* message);
typedef int (__cdecl *ptrSimGetDialogResult)(int genericDialogHandle);
typedef char* (__cdecl *ptrSimGetDialogInput)(int genericDialogHandle);
typedef int (__cdecl *ptrSimEndDialog)(int genericDialogHandle);
typedef int (__cdecl *ptrSimIsObjectInSelection)(int objectHandle);
typedef int (__cdecl *ptrSimAddObjectToSelection)(int what,int objectHandle);
typedef int (__cdecl *ptrSimRemoveObjectFromSelection)(int what,int objectHandle);
typedef int (__cdecl *ptrSimGetObjectSelectionSize)();
typedef int (__cdecl *ptrSimGetObjectLastSelection)();
typedef int (__cdecl *ptrSimGetObjectSelection)(int* objectHandles);
typedef int (__cdecl *ptrSimDeleteSelectedObjects)();
typedef int (__cdecl *ptrSimGetObjectUniqueIdentifier)(int objectHandle,int* uniqueIdentifier);
typedef void (__cdecl *ptr_simSetDynamicJointLocalTransformationPart2IsValid)(void* joint,bool valid);
typedef void (__cdecl *ptr_simSetDynamicForceSensorLocalTransformationPart2IsValid)(void* forceSensor,bool valid);
typedef bool (__cdecl *ptr_simIsForceSensorBroken)(const void* forceSensor);
typedef int (__cdecl *ptrSimBreakForceSensor)(int objectHandle);
typedef int (__cdecl *ptrSimSetScriptText)(int scriptHandle,const char* scriptText);
typedef const char* (__cdecl *ptrSimGetScriptText)(int scriptHandle);
typedef int (__cdecl *ptrSimGetScriptProperty)(int scriptHandle,int* scriptProperty,int* associatedObjectHandle);
typedef void (__cdecl *ptr_simSetGeomProxyDynamicsFullRefreshFlag)(void* geomData,bool flag);
typedef bool (__cdecl *ptr_simGetGeomProxyDynamicsFullRefreshFlag)(const void* geomData);
typedef int (__cdecl *ptrSimRemoveObject)(int objectHandle);
typedef void (__cdecl *ptr_simSetShapeIsStaticAndNotRespondableButDynamicTag)(const void* shape,bool tag);
typedef bool (__cdecl *ptr_simGetShapeIsStaticAndNotRespondableButDynamicTag)(const void* shape);
typedef int (__cdecl *ptrSimGetVisionSensorResolution)(int visionSensorHandle,int* resolution);
typedef unsigned char* (__cdecl *ptrSimGetVisionSensorCharImage)(int visionSensorHandle,int* resolutionX,int* resolutionY);
typedef int (__cdecl *ptrSimSetVisionSensorCharImage)(int visionSensorHandle,const unsigned char* image);
typedef void* (__cdecl *ptrSimBroadcastMessage)(int* auxiliaryData,void* customData,int* replyData);
typedef void* (__cdecl *ptrSimSendModuleMessage)(int message,int* auxiliaryData,void* customData,int* replyData);
typedef bool (__cdecl *ptr_simIsDynamicMotorEnabled)(const void* joint);
typedef bool (__cdecl *ptr_simIsDynamicMotorPositionCtrlEnabled)(const void* joint);
typedef bool (__cdecl *ptr_simIsDynamicMotorTorqueModulationEnabled)(const void* joint);
typedef int (__cdecl *ptr_simGetContactCallbackCount)();
typedef const void* (__cdecl *ptr_simGetContactCallback)(int index);
typedef int (__cdecl *ptr_simGetJointCallbackCallOrder)(const void* joint);
typedef int (__cdecl *ptrSimSetDoubleSignal)(const char* signalName,double signalValue);
typedef int (__cdecl *ptrSimGetDoubleSignal)(const char* signalName,double* signalValue);
typedef int (__cdecl *ptrSimClearDoubleSignal)(const char* signalName);
typedef int (__cdecl *ptrSimRemoveParticleObject)(int objectHandle);
/* deprecated, and previously single precision functions: */
typedef int (__cdecl *ptrSimAddParticleObject)(int objectType,SIMDOUBLE size,SIMDOUBLE density,const void* params,SIMDOUBLE lifeTime,int maxItemCount,const float* color,const float* setToNULL,const float* setToNULL2,const float* setToNULL3);
typedef int (__cdecl *ptrSimAddParticleObjectItem)(int objectHandle,const SIMDOUBLE* itemData);
typedef int (__cdecl *ptrSimJointGetForce)(int jointHandle,SIMDOUBLE* forceOrTorque);
typedef int (__cdecl *ptrSimGetMpConfigForTipPose)(int motionPlanningObjectHandle,int options,SIMDOUBLE closeNodesDistance,int trialCount,const SIMDOUBLE* tipPose,int maxTimeInMs,SIMDOUBLE* outputJointPositions,const SIMDOUBLE* referenceConfigs,int referenceConfigCount,const SIMDOUBLE* jointWeights,const int* jointBehaviour,int correctionPasses);
typedef SIMDOUBLE* (__cdecl *ptrSimFindMpPath)(int motionPlanningObjectHandle,const SIMDOUBLE* startConfig,const SIMDOUBLE* goalConfig,int options,SIMDOUBLE stepSize,int* outputConfigsCnt,int maxTimeInMs,SIMDOUBLE* reserved,const int* auxIntParams,const SIMDOUBLE* auxFloatParams);
typedef SIMDOUBLE* (__cdecl *ptrSimSimplifyMpPath)(int motionPlanningObjectHandle,const SIMDOUBLE* pathBuffer,int configCnt,int options,SIMDOUBLE stepSize,int increment,int* outputConfigsCnt,int maxTimeInMs,SIMDOUBLE* reserved,const int* auxIntParams,const SIMDOUBLE* auxFloatParams);
typedef SIMDOUBLE* (__cdecl *ptrSimFindIkPath)(int motionPlanningObjectHandle,const SIMDOUBLE* startConfig,const SIMDOUBLE* goalPose,int options,SIMDOUBLE stepSize,int* outputConfigsCnt,SIMDOUBLE* reserved,const int* auxIntParams,const SIMDOUBLE* auxFloatParams);
typedef SIMDOUBLE* (__cdecl *ptrSimGetMpConfigTransition)(int motionPlanningObjectHandle,const SIMDOUBLE* startConfig,const SIMDOUBLE* goalConfig,int options,const int* select,SIMDOUBLE calcStepSize,SIMDOUBLE maxOutStepSize,int wayPointCnt,const SIMDOUBLE* wayPoints,int* outputConfigsCnt,const int* auxIntParams,const SIMDOUBLE* auxFloatParams);
typedef int (__cdecl *ptrSimCreateMotionPlanning)(int jointCnt,const int* jointHandles,const int* jointRangeSubdivisions,const SIMDOUBLE* jointMetricWeights,int options,const int* intParams,const SIMDOUBLE* floatParams,const void* reserved);
typedef int (__cdecl *ptrSimSearchPath)(int pathPlanningObjectHandle,SIMDOUBLE maximumSearchTime);
typedef int (__cdecl *ptrSimInitializePathSearch)(int pathPlanningObjectHandle,SIMDOUBLE maximumSearchTime,SIMDOUBLE searchTimeStep);
typedef int (__cdecl *ptrSimHandlePath)(int pathHandle,SIMDOUBLE deltaTime);
typedef int (__cdecl *ptrSimHandleJoint)(int jointHandle,SIMDOUBLE deltaTime);
typedef int (__cdecl *ptrSimSetUIButtonColor)(int uiHandle,int buttonHandle,const float* upStateColor,const float* downStateColor,const float* labelColor);
typedef int (__cdecl *ptrSimSetUIButtonArrayColor)(int uiHandle,int buttonHandle,const int* position,const float* color);
typedef int (__cdecl *ptrSimRegisterContactCallback)(int(*callBack)(int,int,int,int*,SIMDOUBLE*));
typedef int (__cdecl *ptrSimSetJointForce)(int objectHandle,SIMDOUBLE forceOrTorque);
typedef int (__cdecl *ptrSimHandleMill)(int millHandle,SIMDOUBLE* removedSurfaceAndVolume);
typedef int (__cdecl *ptrSimSetShapeMassAndInertia)(int shapeHandle,SIMDOUBLE mass,const SIMDOUBLE* inertiaMatrix,const SIMDOUBLE* centerOfMass,const SIMDOUBLE* transformation);
typedef int (__cdecl *ptrSimGetShapeMassAndInertia)(int shapeHandle,SIMDOUBLE* mass,SIMDOUBLE* inertiaMatrix,SIMDOUBLE* centerOfMass,const SIMDOUBLE* transformation);
typedef int (__cdecl *ptrSimCheckIkGroup)(int ikGroupHandle,int jointCnt,const int* jointHandles,SIMDOUBLE* jointValues,const int* jointOptions);
typedef int (__cdecl *ptrSimCreateIkGroup)(int options,const int* intParams,const SIMDOUBLE* floatParams,const void* reserved);
typedef int (__cdecl *ptrSimCreateIkElement)(int ikGroupHandle,int options,const int* intParams,const SIMDOUBLE* floatParams,const void* reserved);
typedef int (__cdecl *ptrSimGetConfigForTipPose)(int ikGroupHandle,int jointCnt,const int* jointHandles,SIMDOUBLE thresholdDist,int maxTimeInMs,SIMDOUBLE* retConfig,const SIMDOUBLE* metric,int collisionPairCnt,const int* collisionPairs,const int* jointOptions,const SIMDOUBLE* lowLimits,const SIMDOUBLE* ranges,void* reserved);
typedef SIMDOUBLE* (__cdecl *ptrSimGenerateIkPath)(int ikGroupHandle,int jointCnt,const int* jointHandles,int ptCnt,int collisionPairCnt,const int* collisionPairs,const int* jointOptions,void* reserved);
typedef SIMDOUBLE* (__cdecl *ptrSimGetIkGroupMatrix)(int ikGroupHandle,int options,int* matrixSize);
typedef int (__cdecl *ptrSimSetIkGroupProperties)(int ikGroupHandle,int resolutionMethod,int maxIterations,SIMDOUBLE damping,void* reserved);
typedef int (__cdecl *ptrSimGetPositionOnPath)(int pathHandle,SIMDOUBLE relativeDistance,SIMDOUBLE* position);
typedef int (__cdecl *ptrSimGetOrientationOnPath)(int pathHandle,SIMDOUBLE relativeDistance,SIMDOUBLE* eulerAngles);
typedef int (__cdecl *ptrSimGetDataOnPath)(int pathHandle,SIMDOUBLE relativeDistance,int dataType,int* intData,SIMDOUBLE* floatData);
typedef int (__cdecl *ptrSimGetClosestPositionOnPath)(int pathHandle,SIMDOUBLE* absolutePosition,SIMDOUBLE* pathPosition);
typedef int (__cdecl *ptrSimGetPathPosition)(int objectHandle,SIMDOUBLE* position);
typedef int (__cdecl *ptrSimSetPathPosition)(int objectHandle,SIMDOUBLE position);
typedef int (__cdecl *ptrSimGetPathLength)(int objectHandle,SIMDOUBLE* length);
typedef int (__cdecl *ptrSimCreatePath)(int attributes,const int* intParams,const SIMDOUBLE* floatParams,const float* color);
typedef int (__cdecl *ptrSimSetPathTargetNominalVelocity)(int objectHandle,SIMDOUBLE targetNominalVelocity);
typedef int (__cdecl *ptrSimHandleDistance)(int distanceObjectHandle,SIMDOUBLE* smallestDistance);
typedef int (__cdecl *ptrSimReadDistance)(int distanceObjectHandle,SIMDOUBLE* smallestDistance);
typedef int (__cdecl *ptrSimAddBanner)(const char* label,SIMDOUBLE size,int options,const SIMDOUBLE* positionAndEulerAngles,int parentObjectHandle,const float* labelColors,const float* backgroundColors);
typedef int (__cdecl *ptrSimAddGhost)(int ghostGroup,int objectHandle,int options,SIMDOUBLE startTime,SIMDOUBLE endTime,const float* color);
typedef int (__cdecl *ptrSimModifyGhost)(int ghostGroup,int ghostId,int operation,SIMDOUBLE floatValue,int options,int optionsMask,const SIMDOUBLE* colorOrTransformation);
typedef int (__cdecl *ptrSimSetGraphUserData)(int graphHandle,const char* streamName,SIMDOUBLE data);
typedef int (__cdecl *ptrSimCopyMatrix)(const SIMDOUBLE* matrixIn,SIMDOUBLE* matrixOut);
typedef int (__cdecl *ptrSimSetVisionSensorFilter)(int visionSensorHandle,int filterIndex,int options,const int* pSizes,const unsigned char* bytes,const int* ints,const SIMDOUBLE* floats,const unsigned char* custom);
typedef int (__cdecl *ptrSimGetVisionSensorFilter)(int visionSensorHandle,int filterIndex,int* options,int* pSizes,unsigned char** bytes,int** ints,SIMDOUBLE** floats,unsigned char** custom);
typedef int (__cdecl *ptrSimSetIkElementProperties)(int ikGroupHandle,int tipDummyHandle,int constraints,const SIMDOUBLE* precision,const SIMDOUBLE* weight,void* reserved);
typedef int (__cdecl *ptrSimSendData)(int targetID,int dataHeader,const char* dataName,const char* data,int dataLength,int antennaHandle,SIMDOUBLE actionRadius,SIMDOUBLE emissionAngle1,SIMDOUBLE emissionAngle2,SIMDOUBLE persistence);
typedef int (__cdecl *ptrSimSetObjectSizeValues)(int objectHandle,const SIMDOUBLE* sizeValues);
typedef int (__cdecl *ptrSimGetObjectSizeValues)(int objectHandle,SIMDOUBLE* sizeValues);
typedef int (__cdecl *ptrSimDisplayDialog)(const char* titleText,const char* mainText,int dialogType,const char* initialText,const float* titleColors,const float* dialogColors,int* elementHandle);
typedef int (__cdecl *ptrSimScaleSelectedObjects)(SIMDOUBLE scalingFactor,bool scalePositionsToo);
typedef void (__cdecl *ptr_simSetDynamicJointLocalTransformationPart2)(void* joint,const SIMDOUBLE* pos,const SIMDOUBLE* quat);
typedef void (__cdecl *ptr_simSetDynamicForceSensorLocalTransformationPart2)(void* forceSensor,const SIMDOUBLE* pos,const SIMDOUBLE* quat);
typedef void (__cdecl *ptr_simGetDynamicForceSensorLocalTransformationPart2)(const void* forceSensor,SIMDOUBLE* pos,SIMDOUBLE* quat);
typedef int (__cdecl *ptrSimSetScriptAttribute)(int scriptHandle,int attributeID,SIMDOUBLE floatVal,int intOrBoolVal);
typedef int (__cdecl *ptrSimGetScriptAttribute)(int scriptHandle,int attributeID,SIMDOUBLE* floatVal,int* intOrBoolVal);
typedef int (__cdecl *ptrSimGetJointMaxForce)(int jointHandle,SIMDOUBLE* forceOrTorque);
typedef int (__cdecl *ptrSimSetJointMaxForce)(int objectHandle,SIMDOUBLE forceOrTorque);
typedef float* (__cdecl *ptrSimGetVisionSensorImage)(int visionSensorHandle);
typedef int (__cdecl *ptrSimSetVisionSensorImage)(int visionSensorHandle,const float* image);
typedef float* (__cdecl *ptrSimGetVisionSensorDepthBuffer)(int visionSensorHandle);
typedef int (__cdecl *ptrSimCreatePureShape)(int primitiveType,int options,const SIMDOUBLE* sizes,SIMDOUBLE mass,const int* precision);
typedef void (__cdecl *ptr_simGetMotorPid)(const void* joint,SIMDOUBLE* pParam,SIMDOUBLE* iParam,SIMDOUBLE* dParam);
typedef int (__cdecl *ptrSimBuildMatrixQ)(const SIMDOUBLE* position,const SIMDOUBLE* quaternion,SIMDOUBLE* matrix);
typedef int (__cdecl *ptrSimGetQuaternionFromMatrix)(const SIMDOUBLE* matrix,SIMDOUBLE* quaternion);
typedef void (__cdecl *ptr_simGetPrincipalMomentOfInertia)(const void* geomInfo,SIMDOUBLE* inertia);
typedef void (__cdecl *ptr_simGetLocalInertiaFrame)(const void* geomInfo,SIMDOUBLE* pos,SIMDOUBLE* quat);
typedef int (__cdecl *ptrSimGetShapeVertex)(int shapeHandle,int groupElementIndex,int vertexIndex,SIMDOUBLE* relativePosition);
typedef int (__cdecl *ptrSimGetShapeTriangle)(int shapeHandle,int groupElementIndex,int triangleIndex,int* vertexIndices,SIMDOUBLE* triangleNormals);


extern ptrSimGetShapeMaterial simGetShapeMaterial;
extern ptrSimHandleVarious simHandleVarious;
extern ptrSimSerialPortOpen simSerialPortOpen;
extern ptrSimSerialPortClose simSerialPortClose;
extern ptrSimSerialPortSend simSerialPortSend;
extern ptrSimSerialPortRead simSerialPortRead;
extern ptrSimJointGetForce simJointGetForce;
extern ptrSimGetPathPlanningHandle simGetPathPlanningHandle;
extern ptrSimGetMotionPlanningHandle simGetMotionPlanningHandle;
extern ptrSimGetMpConfigForTipPose simGetMpConfigForTipPose;
extern ptrSimFindMpPath simFindMpPath;
extern ptrSimSimplifyMpPath simSimplifyMpPath;
extern ptrSimFindIkPath simFindIkPath;
extern ptrSimGetMpConfigTransition simGetMpConfigTransition;
extern ptrSimCreateMotionPlanning simCreateMotionPlanning;
extern ptrSimRemoveMotionPlanning simRemoveMotionPlanning;
extern ptrSimSearchPath simSearchPath;
extern ptrSimInitializePathSearch simInitializePathSearch;
extern ptrSimPerformPathSearchStep simPerformPathSearchStep;
extern ptrSimLockInterface simLockInterface;
extern ptrSimCopyPasteSelectedObjects simCopyPasteSelectedObjects;
extern ptrSimResetPath simResetPath;
extern ptrSimHandlePath simHandlePath;
extern ptrSimResetJoint simResetJoint;
extern ptrSimHandleJoint simHandleJoint;
extern ptrSimAppendScriptArrayEntry simAppendScriptArrayEntry;
extern ptrSimClearScriptVariable simClearScriptVariable;
extern ptr_simGetJointOdeParameters _simGetJointOdeParameters;
extern ptr_simGetJointBulletParameters _simGetJointBulletParameters;
extern ptr_simGetOdeMaxContactFrictionCFMandERP _simGetOdeMaxContactFrictionCFMandERP;
extern ptr_simGetBulletCollisionMargin _simGetBulletCollisionMargin;
extern ptr_simGetBulletStickyContact _simGetBulletStickyContact;
extern ptr_simGetBulletRestitution _simGetBulletRestitution;
extern ptr_simGetVortexParameters _simGetVortexParameters;
extern ptr_simGetNewtonParameters _simGetNewtonParameters;
extern ptr_simGetDamping _simGetDamping;
extern ptr_simGetFriction _simGetFriction;
extern ptrSimAddSceneCustomData simAddSceneCustomData;
extern ptrSimGetSceneCustomDataLength simGetSceneCustomDataLength;
extern ptrSimGetSceneCustomData simGetSceneCustomData;
extern ptrSimAddObjectCustomData simAddObjectCustomData;
extern ptrSimGetObjectCustomDataLength simGetObjectCustomDataLength;
extern ptrSimGetObjectCustomData simGetObjectCustomData;
extern ptrSimCreateUI simCreateUI;
extern ptrSimCreateUIButton simCreateUIButton;
extern ptrSimGetUIHandle simGetUIHandle;
extern ptrSimGetUIProperty simGetUIProperty;
extern ptrSimGetUIEventButton simGetUIEventButton;
extern ptrSimSetUIProperty simSetUIProperty;
extern ptrSimGetUIButtonProperty simGetUIButtonProperty;
extern ptrSimSetUIButtonProperty simSetUIButtonProperty;
extern ptrSimGetUIButtonSize simGetUIButtonSize;
extern ptrSimSetUIButtonLabel simSetUIButtonLabel;
extern ptrSimGetUIButtonLabel simGetUIButtonLabel;
extern ptrSimSetUISlider simSetUISlider;
extern ptrSimGetUISlider simGetUISlider;
extern ptrSimSetUIButtonColor simSetUIButtonColor;
extern ptrSimSetUIButtonTexture simSetUIButtonTexture;
extern ptrSimCreateUIButtonArray simCreateUIButtonArray;
extern ptrSimSetUIButtonArrayColor simSetUIButtonArrayColor;
extern ptrSimDeleteUIButtonArray simDeleteUIButtonArray;
extern ptrSimRemoveUI simRemoveUI;
extern ptrSimSetUIPosition simSetUIPosition;
extern ptrSimGetUIPosition simGetUIPosition;
extern ptrSimLoadUI simLoadUI;
extern ptrSimSaveUI simSaveUI;
extern ptrSimHandleGeneralCallbackScript simHandleGeneralCallbackScript;
extern ptrSimRegisterCustomLuaFunction simRegisterCustomLuaFunction;
extern ptrSimRegisterCustomLuaVariable simRegisterCustomLuaVariable;
extern ptrSimRegisterContactCallback simRegisterContactCallback;
extern ptrSimGetMechanismHandle simGetMechanismHandle;
extern ptrSimHandleMechanism simHandleMechanism;
extern ptrSimHandleCustomizationScripts simHandleCustomizationScripts;
extern ptrSimCallScriptFunction simCallScriptFunction;
extern ptrSimSetVisionSensorFilter simSetVisionSensorFilter;
extern ptrSimGetVisionSensorFilter simGetVisionSensorFilter;
extern ptrSimGetScriptSimulationParameter simGetScriptSimulationParameter;
extern ptrSimSetScriptSimulationParameter simSetScriptSimulationParameter;
extern ptrSimSetJointForce simSetJointForce;
extern ptrSimHandleMill simHandleMill;
extern ptrSimResetMill simResetMill;
extern ptrSimResetMilling simResetMilling;
extern ptrSimApplyMilling simApplyMilling;
extern ptr_simGetParentFollowsDynamic _simGetParentFollowsDynamic;
extern ptrSimGetNameSuffix simGetNameSuffix;
extern ptrSimSetNameSuffix simSetNameSuffix;
extern ptrSimAddStatusbarMessage simAddStatusbarMessage;
extern ptrSimGetScriptRawBuffer simGetScriptRawBuffer;
extern ptrSimSetScriptRawBuffer simSetScriptRawBuffer;
extern ptrSimReleaseScriptRawBuffer simReleaseScriptRawBuffer;
extern ptrSimSetShapeMassAndInertia simSetShapeMassAndInertia;
extern ptrSimGetShapeMassAndInertia simGetShapeMassAndInertia;
extern ptrSimCheckIkGroup simCheckIkGroup;
extern ptrSimCreateIkGroup simCreateIkGroup;
extern ptrSimRemoveIkGroup simRemoveIkGroup;
extern ptrSimCreateIkElement simCreateIkElement;
extern ptrSimExportIk simExportIk;
extern ptrSimComputeJacobian simComputeJacobian;
extern ptrSimGetConfigForTipPose simGetConfigForTipPose;
extern ptrSimGenerateIkPath simGenerateIkPath;
extern ptrSimGetIkGroupHandle simGetIkGroupHandle;
extern ptrSimGetIkGroupMatrix simGetIkGroupMatrix;
extern ptrSimHandleIkGroup simHandleIkGroup;
extern ptrSimSetIkGroupProperties simSetIkGroupProperties;
extern ptrSimSetIkElementProperties simSetIkElementProperties;
extern ptrSimSetThreadIsFree simSetThreadIsFree;
extern ptrSimTubeOpen simTubeOpen;
extern ptrSimTubeClose simTubeClose;
extern ptrSimTubeWrite simTubeWrite;
extern ptrSimTubeRead simTubeRead;
extern ptrSimTubeStatus simTubeStatus;
extern ptrSimSendData simSendData;
extern ptrSimReceiveData simReceiveData;
extern ptrSimGetPositionOnPath simGetPositionOnPath;
extern ptrSimGetDataOnPath simGetDataOnPath;
extern ptrSimGetOrientationOnPath simGetOrientationOnPath;
extern ptrSimGetClosestPositionOnPath simGetClosestPositionOnPath;
extern ptrSimGetPathPosition simGetPathPosition;
extern ptrSimSetPathPosition simSetPathPosition;
extern ptrSimGetPathLength simGetPathLength;
extern ptrSimCreatePath simCreatePath;
extern ptrSimInsertPathCtrlPoints simInsertPathCtrlPoints;
extern ptrSimCutPathCtrlPoints simCutPathCtrlPoints;
extern ptrSimGetThreadId simGetThreadId;
extern ptrSimSwitchThread simSwitchThread;
extern ptrSimLockResources simLockResources;
extern ptrSimUnlockResources simUnlockResources;
extern ptrSimGetUserParameter simGetUserParameter;
extern ptrSimSetUserParameter simSetUserParameter;
extern ptrSimSetPathTargetNominalVelocity simSetPathTargetNominalVelocity;
extern ptrSimGetCollectionHandle simGetCollectionHandle;
extern ptrSimRemoveCollection simRemoveCollection;
extern ptrSimEmptyCollection simEmptyCollection;
extern ptrSimGetCollectionName simGetCollectionName;
extern ptrSimSetCollectionName simSetCollectionName;
extern ptrSimCreateCollection simCreateCollection;
extern ptrSimAddObjectToCollection simAddObjectToCollection;
extern ptrSimGetCollisionHandle simGetCollisionHandle;
extern ptrSimGetDistanceHandle simGetDistanceHandle;
extern ptrSimResetCollision simResetCollision;
extern ptrSimResetDistance simResetDistance;
extern ptrSimHandleCollision simHandleCollision;
extern ptrSimReadCollision simReadCollision;
extern ptrSimHandleDistance simHandleDistance;
extern ptrSimReadDistance simReadDistance;
extern ptrSimAddBanner simAddBanner;
extern ptrSimRemoveBanner simRemoveBanner;
extern ptrSimAddGhost simAddGhost;
extern ptrSimModifyGhost simModifyGhost;
extern ptrSimSetGraphUserData simSetGraphUserData;
extern ptrSimAddPointCloud simAddPointCloud;
extern ptrSimModifyPointCloud simModifyPointCloud;
extern ptrSimCopyMatrix simCopyMatrix;
extern ptrSimGetObjectInt32Param simGetObjectIntParameter;
extern ptrSimSetObjectInt32Param simSetObjectIntParameter;
extern ptrSimGetObjectInt32Param simGetObjectInt32Parameter;
extern ptrSimSetObjectInt32Param simSetObjectInt32Parameter;
extern ptrSimGetObjectFloatParam simGetObjectFloatParameter;
extern ptrSimSetObjectFloatParam simSetObjectFloatParameter;
extern ptrSimGetObjectStringParam simGetObjectStringParameter;
extern ptrSimSetObjectStringParam simSetObjectStringParameter;
extern ptrSimSetBoolParam simSetBooleanParameter;
extern ptrSimGetBoolParam simGetBooleanParameter;
extern ptrSimSetBoolParam simSetBoolParameter;
extern ptrSimGetBoolParam simGetBoolParameter;
extern ptrSimSetInt32Param simSetIntegerParameter;
extern ptrSimGetInt32Param simGetIntegerParameter;
extern ptrSimSetInt32Param simSetInt32Parameter;
extern ptrSimGetInt32Param simGetInt32Parameter;
extern ptrSimGetUInt64Param simGetUInt64Parameter;
extern ptrSimSetFloatParam simSetFloatingParameter;
extern ptrSimGetFloatParam simGetFloatingParameter;
extern ptrSimSetFloatParam simSetFloatParameter;
extern ptrSimGetFloatParam simGetFloatParameter;
extern ptrSimSetStringParam simSetStringParameter;
extern ptrSimGetStringParam simGetStringParameter;
extern ptrSimSetArrayParam simSetArrayParameter;
extern ptrSimGetArrayParam simGetArrayParameter;
extern ptrSimGetEngineFloatParam simGetEngineFloatParameter;
extern ptrSimGetEngineInt32Param simGetEngineInt32Parameter;
extern ptrSimGetEngineBoolParam simGetEngineBoolParameter;
extern ptrSimSetEngineFloatParam simSetEngineFloatParameter;
extern ptrSimSetEngineInt32Param simSetEngineInt32Parameter;
extern ptrSimSetEngineBoolParam simSetEngineBoolParameter;
extern ptrSimIsHandle simIsHandleValid;
extern ptrSimAddModuleMenuEntry simAddModuleMenuEntry;
extern ptrSimSetModuleMenuItemState simSetModuleMenuItemState;
extern ptrSimSetInt32Signal simSetIntegerSignal;
extern ptrSimGetInt32Signal simGetIntegerSignal;
extern ptrSimClearInt32Signal simClearIntegerSignal;
extern ptrSimGetObjectName simGetObjectName;
extern ptrSimSetObjectName simSetObjectName;
extern ptrSimGetScriptName simGetScriptName;
extern ptrSimGetScriptHandle simGetScriptHandle;
extern ptrSimSetScriptVariable simSetScriptVariable;
extern ptrSimGetObjectHandle simGetObjectHandle;
extern ptrSimGetScript simGetScript;
extern ptrSimGetScriptAssociatedWithObject simGetScriptAssociatedWithObject;
extern ptrSimGetCustomizationScriptAssociatedWithObject simGetCustomizationScriptAssociatedWithObject;
extern ptrSimGetObjectAssociatedWithScript simGetObjectAssociatedWithScript;
extern ptrSimGetObjectConfiguration simGetObjectConfiguration;
extern ptrSimSetObjectConfiguration simSetObjectConfiguration;
extern ptrSimGetConfigurationTree simGetConfigurationTree;
extern ptrSimSetConfigurationTree simSetConfigurationTree;
extern ptrSimEnableEventCallback simEnableEventCallback;
extern ptrSimSetObjectSizeValues simSetObjectSizeValues;
extern ptrSimGetObjectSizeValues simGetObjectSizeValues;
extern ptrSimGetSystemTimeInMilliseconds simGetSystemTimeInMilliseconds;
extern ptrSimGetSystemTimeInMs simGetSystemTimeInMs;
extern ptrSimFileDialog simFileDialog;
extern ptrSimMsgBox simMsgBox;
extern ptrSimDisplayDialog simDisplayDialog;
extern ptrSimGetDialogResult simGetDialogResult;
extern ptrSimGetDialogInput simGetDialogInput;
extern ptrSimEndDialog simEndDialog;
extern ptrSimIsObjectInSelection simIsObjectInSelection;
extern ptrSimAddObjectToSelection simAddObjectToSelection;
extern ptrSimRemoveObjectFromSelection simRemoveObjectFromSelection;
extern ptrSimGetObjectSelectionSize simGetObjectSelectionSize;
extern ptrSimGetObjectLastSelection simGetObjectLastSelection;
extern ptrSimGetObjectSelection simGetObjectSelection;
extern ptrSimScaleSelectedObjects simScaleSelectedObjects;
extern ptrSimDeleteSelectedObjects simDeleteSelectedObjects;
extern ptrSimSetNamedStringParam simSetStringNamedParam;
extern ptrSimGetNamedStringParam simGetStringNamedParam;
extern ptrSimGetObjectUniqueIdentifier simGetObjectUniqueIdentifier;
extern ptr_simSetDynamicJointLocalTransformationPart2 _simSetDynamicJointLocalTransformationPart2;
extern ptr_simSetDynamicForceSensorLocalTransformationPart2 _simSetDynamicForceSensorLocalTransformationPart2;
extern ptr_simSetDynamicJointLocalTransformationPart2IsValid _simSetDynamicJointLocalTransformationPart2IsValid;
extern ptr_simSetDynamicForceSensorLocalTransformationPart2IsValid _simSetDynamicForceSensorLocalTransformationPart2IsValid;
extern ptr_simIsForceSensorBroken _simIsForceSensorBroken;
extern ptrSimBreakForceSensor simBreakForceSensor;
extern ptr_simGetDynamicForceSensorLocalTransformationPart2 _simGetDynamicForceSensorLocalTransformationPart2;
extern ptrSimGetJointMatrix simGetJointMatrix;
extern ptrSimSetSphericalJointMatrix simSetSphericalJointMatrix;
extern ptrSimGetObjectHandleEx simGetObjectHandleEx;
extern ptrSimSetScriptAttribute simSetScriptAttribute;
extern ptrSimGetScriptAttribute simGetScriptAttribute;
extern ptrSimSetScriptText simSetScriptText;
extern ptrSimGetScriptText simGetScriptText;
extern ptrSimGetScriptProperty simGetScriptProperty;
extern ptrSimGetJointMaxForce simGetJointMaxForce;
extern ptrSimSetJointMaxForce simSetJointMaxForce;
extern ptr_simSetGeomProxyDynamicsFullRefreshFlag _simSetGeomProxyDynamicsFullRefreshFlag;
extern ptr_simGetGeomProxyDynamicsFullRefreshFlag _simGetGeomProxyDynamicsFullRefreshFlag;
extern ptrSimRemoveObject simRemoveObject;
extern ptr_simSetShapeIsStaticAndNotRespondableButDynamicTag _simSetShapeIsStaticAndNotRespondableButDynamicTag;
extern ptr_simGetShapeIsStaticAndNotRespondableButDynamicTag _simGetShapeIsStaticAndNotRespondableButDynamicTag;
extern ptrSimGetVisionSensorResolution simGetVisionSensorResolution;
extern ptrSimGetVisionSensorImage simGetVisionSensorImage;
extern ptrSimGetVisionSensorCharImage simGetVisionSensorCharImage;
extern ptrSimSetVisionSensorImage simSetVisionSensorImage;
extern ptrSimSetVisionSensorCharImage simSetVisionSensorCharImage;
extern ptrSimGetVisionSensorDepthBuffer simGetVisionSensorDepthBuffer;
extern ptrSimCreatePureShape simCreatePureShape;
extern ptrSimBroadcastMessage simBroadcastMessage;
extern ptrSimSendModuleMessage simSendModuleMessage;
extern ptr_simIsDynamicMotorEnabled _simIsDynamicMotorEnabled;
extern ptr_simIsDynamicMotorPositionCtrlEnabled _simIsDynamicMotorPositionCtrlEnabled;
extern ptr_simIsDynamicMotorTorqueModulationEnabled _simIsDynamicMotorTorqueModulationEnabled;
extern ptr_simGetMotorPid _simGetMotorPid;
extern ptr_simGetContactCallbackCount _simGetContactCallbackCount;
extern ptr_simGetContactCallback _simGetContactCallback;
extern ptrSimBuildMatrixQ simBuildMatrixQ;
extern ptrSimGetQuaternionFromMatrix simGetQuaternionFromMatrix;
extern ptr_simGetLocalInertiaFrame _simGetLocalInertiaFrame;
extern ptr_simGetPrincipalMomentOfInertia _simGetPrincipalMomentOfInertia;
extern ptr_simGetJointCallbackCallOrder _simGetJointCallbackCallOrder;
extern ptrSimSetDoubleSignal simSetDoubleSignal;
extern ptrSimGetDoubleSignal simGetDoubleSignal;
extern ptrSimClearDoubleSignal simClearDoubleSignal;
extern ptrSimAddParticleObject simAddParticleObject;
extern ptrSimRemoveParticleObject simRemoveParticleObject;
extern ptrSimAddParticleObjectItem simAddParticleObjectItem;
extern ptrSimGetShapeVertex simGetShapeVertex;
extern ptrSimGetShapeTriangle simGetShapeTriangle;
