import smtplib
from email.mime.text import MIMEText

def send_email(sender, recipient, subject, body, smtp_password):
    msg = MIMEText(body)
    msg['Subject'] = subject
    msg['From'] = sender
    msg['To'] = recipient

    try:
        with smtplib.SMTP('smtp.gmail.com', 587) as server:
            server.starttls()
            server.login(sender, smtp_password)
            server.sendmail(sender, [recipient], msg.as_string())

    except Exception as e:
        print(f"Failed to send email: {e}")