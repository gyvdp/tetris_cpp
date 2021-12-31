// MIT License
//
// Copyright (c) 2021 Andrew SASSOYE, Constantin GUNDUZ, Gregory VAN DER PLUIJM,
// Thomas LEUTSCHER
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_GAME_STATE_EXCEPTIONS_NOTSTARTEDEXCEPTION_H_
#define ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_GAME_STATE_EXCEPTIONS_NOTSTARTEDEXCEPTION_H_

namespace tetris::model::game::states::exceptions {

/**
 * @brief Throws an exception signaling the game has not been started.
 */
class notStartedException : public std::logic_error {
 public:
  /**
   * @brief Constructor for not started exception.
   * @param mess Message to display in exception.
   */
  explicit notStartedException(const std::string& mess, const char* file,
                               int line)
      : std::logic_error(std::string(file) + ":" + std::to_string(line) + ":" +
                         arg){};
  virtual ~notStartedException() = default;

  /**
   * @brief Returns the message of the exception.
   * @return Message of thrown exception.
   */
  [[nodiscard]] const char* what() const noexcept { return msg.c_str(); }
};

}  // namespace tetris::model::game::states::exceptions

#endif  // ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_GAME_STATE_EXCEPTIONS_NOTSTARTEDEXCEPTION_H_
