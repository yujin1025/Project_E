UPJERotateComponent


회전 각도 제한 : Offset으로 설정
...
RotationAngle 	(회전 각도)
RotationOffset 	(각도 제한을 위한 Offset)
RotationSpeed 	(회전 속도 + 방향)
bIsRotating 	(회전 하는지 여부)
bIsReset		(복귀하는지 여부)
OriginalRotation	(복귀를 위한 원위치 저장)

3종류 : 복귀, 회전, 정지
bIsRotating	false		bIsReset	false	: 정지
bIsRotating	false		bIsReset	true	: 복귀
bIsRotating	true		bIsReset	false	: 회전
bIsRotating	true		bIsReset	true	: 사용 안함
--> Enum으로 상태 조절하는것도 고려

-> 돌아가는 함수 있어야 함 : ResetRotation()

Function

변수들에 Getter Setter 설정
각 상태당 Function 하나씩
1. GetRotation -> 회전 시작
2. StopRotation -> 회전 정지
3. UndoRotation -> 복귀


- GetRotation
	오브젝트를 회전시키는 함수, 지정된 Offset까지 물체를 회전시킨다
- StopRotation
	오브젝트를 정지시키는 함수. 현재 회전 각도를 유지한다. 없어도 될듯 함
- UndoRotation
	오브젝트를 원 상태로 되돌리는 함수. GetRotation의 역방향 회전이다. Target은 OriginalRotation