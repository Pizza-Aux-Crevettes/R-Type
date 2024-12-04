const { execSync } = require('child_process');

function validateCommitMessage(commitMessage) {
    const rules = [
        {
            regex: /^ADD:/,
            error: 'The commit norme must be : ADD: FIX: DOCS: STYLE: REFACTOR: TEST: RM: '
        },
        {
            regex: /^FIX:/,
            error: 'The commit norme must be : ADD: FIX: DOCS: STYLE: REFACTOR: TEST: RM: '
        },
        {
            regex: /^DOCS:/,
            error: 'The commit norme must be : ADD: FIX: DOCS: STYLE: REFACTOR: TEST: RM: '
        },
        {
            regex: /^STYLE:/,
            error: 'The commit norme must be : ADD: FIX: DOCS: STYLE: REFACTOR: TEST: RM: '
        },
        {
            regex: /^REFACTOR:/,
            error: 'The commit norme must be : ADD: FIX: DOCS: STYLE: REFACTOR: TEST: RM: '
        },
        {
            regex: /^TEST:/,
            error: 'The commit norme must be : ADD: FIX: DOCS: STYLE: REFACTOR: TEST: RM: '
        },
        {
            regex: /^RM:/,
            error: 'The commit norme must be : ADD: FIX: DOCS: STYLE: REFACTOR: TEST: RM: '
        },
    ];
    const isValid = rules.some(rule => rule.regex.test(commitMessage));

    if (!isValid) {
        console.error(`❌ Invalid commit message: "${commitMessage}"`);
        console.error('🔍 Example: ADD: Description of the commit');
        console.error(rules[0].error);
        process.exit(1);
    }
}

function main() {
    const commits = execSync('git log --format=%s origin/main..HEAD')
        .toString()
        .trim()
        .split('\n');

    for (const message of commits) {
        validateCommitMessage(message);
    }

    console.log('✅ Tous les messages de commit sont valides.');
}

main();