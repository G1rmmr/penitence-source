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

#pragma once

/**
 * @file
 * @brief 스프라이트 컴포넌트
 * 
 * 스프라이트를 렌더링 하는데에 필요한 데이터.
 */

#include <SFML/Graphics.hpp>
#include <memory>

#include "Component.hpp"

namespace MIR
{
    /**
     * @brief 렌더링 가능한 스프라이트 정보를 담는 컴포넌트
     * 
     * 이 컴포넌트는 SFML의 텍스처(sf::Texture)와 스프라이트(sf::Sprite) 관리.
     * 엔티티에 부착함으로써 그래픽 렌더링 가능.
     * width, height 필드는 스프라이트의 가로, 세로 크기를 저장.
     */
    struct Sprite final : public Component
    {
        /**
         * @brief 스프라이트에 할당할 텍스처를 가리키는 shared_ptr
         * 
         * std::shared_ptr를 사용하여 텍스처 리소스를 공유하고, 
         * 텍스처가 더 이상 필요하지 않을 때 자동으로 메모리 해제.
         */
        std::shared_ptr<sf::Texture> texture;

        /**
         * @brief SFML의 스프라이트 객체
         * 
         * texture를 할당받은 후, sprite에 텍스처를 설정함으로써 
         * 실제 화면에 렌더링 가능한 그래픽 개체를 정의.
         */
        sf::Sprite sprite;

        /**
         * @brief 스프라이트의 폭(가로 길이)
         * 
         * 엔티티 그래픽의 실제 가로 길이.
         */
        std::uint16_t width;

        /**
         * @brief 스프라이트의 높이(세로 길이)
         * 
         * 엔티티 그래픽의 실제 세로 길이.
         */
        std::uint16_t height;

        /**
         * @brief 기본 생성자
         * 
         * texture를 nullptr로, width와 height를 0으로 초기화.
         * 텍스처가 설정되지 않은 상태로 시작하며, 이후 필요 시 setTexture를 호출하거나
         * 다른 생성자를 통해 텍스처 지정 가능.
         */
        Sprite() : texture(nullptr), sprite(), width(0), height(0)
        {
        }

        /**
         * @brief 텍스처를 지정하는 생성자
         * 
         * @param texture 스프라이트에 적용할 텍스처의 shared_ptr
         * 
         * texture가 유효한 경우 sprite에 텍스처 설정.
         * width, height는 0으로 초기화되며, 필요 시 이후에 설정 가능.
         */
        Sprite(std::shared_ptr<sf::Texture> texture)
            : texture(texture), sprite(), width(0), height(0)
        {
            if(texture)
                sprite.setTexture(*texture);
        }

        /**
         * @brief 텍스처와 스프라이트 크기를 지정하는 생성자
         * 
         * @param texture 스프라이트에 적용할 텍스처의 shared_ptr
         * @param width 스프라이트의 가로 길이
         * @param height 스프라이트의 세로 길이
         * 
         * texture가 유효한 경우 sprite에 텍스처를 설정하고, 
         * 지정한 width와 height를 통해 이후 렌더링 논리나 충돌 판정에 활용 가능.
         */
        Sprite(std::shared_ptr<sf::Texture> texture, std::uint16_t width, std::uint16_t height)
            : texture(texture), sprite(), width(width), height(height)
        {
            if(texture)
                sprite.setTexture(*texture);
        }
    };
}
