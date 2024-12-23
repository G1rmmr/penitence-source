// Created on Wed Oct 30 2024
// © 2024 BLACKHAND Studio. All rights reserved.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//      http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "core/Game.hpp"

int main()
{
    MIR::Game game;
    game.Init();        ///< 게임 초기화: 리소스 로딩, ECS 세팅, 윈도우 생성 등

    while(game.IsRunning())  
        game.Run();     ///< 게임 루프 실행: 입력 처리, 업데이트, 렌더링

    game.Shutdown();    ///< 게임 종료 처리: 자원 해제, 파일 저장, 로그 출력 등
    return 0;
}
