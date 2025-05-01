async function main() {
    const PAYLOAD = window.workingDir + '/kstuff-toggle.elf';

    return {
        mainText: "Kstuff toggle",
        secondaryText: 'Enable or disable kstuff',
	onclick: async () => {
	    return {
		path: PAYLOAD,
                daemon: true
	    };
        }
    };
}
