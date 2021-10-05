	function sendForm(form, receiveFunc, url)
	{
		var req = new XMLHttpRequest();
		req.addEventListener('load', function(e)
		{
			var data = e.target;
			var response = data.responseText;
			receiveFunc(JSON.parse(response));
		});
		req.open('POST', url);
		req.responseType = 'text';
		req.send(form);
	}
	function createMyForm(message)
	{
		var form = new FormData();
		for (item  = 0; item < message.length; item++)
			if (message[item].value != "")
				form.append(message[item].name, message[item].value);

		return form;
	}
	function createMessage() 
	{
		return InputBlock.querySelectorAll("input");
	}