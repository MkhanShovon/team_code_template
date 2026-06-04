/**
 * Author: Monjur Hossain Khan, OpenAI Codex
 * License: CC0
 * Description: Prefix sum formulas for 1D/2D/3D.
 * Time: O(1)
 * Status: reference
 */
#pragma once

// 1D: S[i + 1] = S[i] + a[i]
// 2D: S[i][j] = S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1] + a[i][j]
// 3D: S[i][j][k] = S[i - 1][j][k] + S[i][j - 1][k] + S[i][j][k - 1]
//      - S[i - 1][j - 1][k] - S[i][j - 1][k - 1] - S[i - 1][j][k - 1]
//      + S[i - 1][j - 1][k - 1] + a[i][j][k]
