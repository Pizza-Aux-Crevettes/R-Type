
# Commit Standard for R-Type

This document outlines the commit standard applied on R-Type project. This convention ensures clear and structured messages for better readability and code management.

---

## Commit Message Structure

Each commit message must follow this format:
```
<TYPE>: <DESCRIPTION>
```
- **TYPE**: The type of change, written in **uppercase**.
- **DESCRIPTION**: A concise and precise description of the modification.

### Main Types

| Type         | Description                                                            |
|--------------|------------------------------------------------------------------------|
| **ADD**      | Adding a new feature                                                   |
| **FIX**      | Fixing a bug                                                           |
| **DOCS**     | Modifying or adding documentation                                      |
| **STYLE**    | Changes related to formatting (e.g., spaces) without functional impact |
| **REFACTOR** | Refactoring code without adding features or fixing bugs                |
| **TEST**     | Adding or updating tests                                               |
| **RM**       | Remove one thing                                                       |

### Example Messages

- **Adding a feature**:
  ```
  ADD: collision system for missiles
  ```

- **Fixing a bug**:
  ```
  FIX: Fixed crash when moving player
  ```

- **Updating documentation**:
  ```
  DOCS: Updated installation instructions
  ```

- **Improving style**:
  ```
  STYLE: Applying clang-format to source files
  ```

---

## Additional Rules

- **Language**: All commit messages must be written in English.
- **Length**: Descriptions should fit in a single line (around 72 characters).
- **Conciseness**: Avoid unnecessary details. Detailed explanations must be added in an extended description.

### Extended Format
For complex commits, you must add an extended description after a blank line:
```
<TYPE>: <DESCRIPTION>

<EXTENDED DESCRIPTION>
```

Example:
```
FIX: Fixed poorly rendered borders on enemies

Borders were misaligned due to a problem in the method
render() of the Enemy object. The function has been fixed to handle sizes.
```

---